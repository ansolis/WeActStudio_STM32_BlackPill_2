import pywinusb.hid as hid

# Read the name of device with PID 0x5750 and VID 0x0483
VID = 0x0483
PID = 0x5750

filter = hid.HidDeviceFilter(vendor_id=VID, product_id=PID)
devices = filter.get_devices()

if devices:
    device = devices[0]
    device.open()
    print(f"Device Name: {device.product_name}")
    feature_report = device.find_feature_reports()
    report_id = 3
    report = next((r for r in feature_report if r.report_id == report_id), None)
    if report:
        buf = [report_id] + list(range(0, 63))
        report.send(buf)
        print(f"Sent Feature Report {report_id}: {buf}")
        # Optionally, read back to verify
        data = report.get()
        print(f"Read Feature Report {report_id} data (len={len(data)}): {data}")
    else:
        print(f"Feature Report {report_id} not found.")
    device.close()
else:
    print("Device not found.")


def input_report_handler(data):
    print(f"Received Input Report (len={len(data)}): {data}")


# Print an input report
if devices:
    device = devices[0]
    device.open()

    # Set up input report handler for report ID 1 (first byte == 1)
    device.set_raw_data_handler(
        lambda data: input_report_handler(data) if data[0] == 1 else None
    )

    print("Waiting for input report with ID 1 (press Ctrl+C to exit)...")
    try:
        import time
        while True:
            time.sleep(0.1)
    except KeyboardInterrupt:
        print("Exiting.")
    device.close()
else:
    print("Device not found.")
