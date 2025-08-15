import pywinusb.hid as hid

# Read the name of device with PID 0x5750 and VID 0x0483
VID = 0x0483
PID = 0x5750

INPUT_REPORT_ID   = 1
OUTPUT_REPORT_ID  = 2
FEATURE_REPORT_ID = 3

def main():
    device = find_device(VID, PID)
    if device is None:
        print("ERROR: Device not found.")
        return

    print(f"Device Name: {device.product_name}")

    # Now device is open
    feature_report = find_feature_report(device, FEATURE_REPORT_ID)
    if feature_report is None:
         print(f"Feature report {FEATURE_REPORT_ID} not found.")
    else:
        data = [FEATURE_REPORT_ID] + [0xA] * 63  # list(range(0, 63))
        send_report(feature_report, data)

        data = read_feature_report(feature_report)
        print_report(data)

    output_report = find_output_report(device, OUTPUT_REPORT_ID)
    if output_report is None:
         print(f"Output report {OUTPUT_REPORT_ID} not found.")
    else:
        data = [OUTPUT_REPORT_ID] + [0xB] * 63
        send_report(output_report, data)

        data = read_feature_report(feature_report)
        print_report(data)

    register_input_report_handler(device, INPUT_REPORT_ID)
    print(f"Waiting for input report with ID {INPUT_REPORT_ID} (press Ctrl+C to exit)...")
    wait_for_ctrl_c()
    device.close()


def find_device(vid, pid):
    filter = hid.HidDeviceFilter(vendor_id=vid, product_id=pid)
    devices = filter.get_devices()
    device = None
    if devices:
        device = devices[0]
        device.open()

    return device


def find_feature_report(device, report_id):
    feature_report = device.find_feature_reports()
    report = next((r for r in feature_report if r.report_id == report_id), None)
    return report


def find_output_report(device, report_id):
    output_reports = device.find_output_reports()
    report = next((r for r in output_reports if r.report_id == report_id), None)
    return report


def send_report(report, buf):
    report_id = buf[0]
    if report is None:
        print(f"Report {report_id} not found.")

    report.send(buf)
    print(f"Sent report {report_id}: {buf}")


def read_feature_report(feature_report):
    data = feature_report.get()
    return data


def input_report_handler(data):
    print(f"Received Input Report (len={len(data)}): {data}")


def register_input_report_handler(device, report_id):
    # Set up input report handler for report ID report_id
    device.set_raw_data_handler(
        lambda data: input_report_handler(data) if data[0] == report_id else None
    )


def print_report(data):
    hex_data = " ".join(f"0x{b:X}" for b in data)
    print(f"Feature report {data[0]} returned: (len={len(data)}); {hex_data}")


def wait_for_ctrl_c():
    try:
        import time
        while True:
            time.sleep(0.1)
    except KeyboardInterrupt:
        print("Exiting.")


if __name__ == "__main__":
    main()
