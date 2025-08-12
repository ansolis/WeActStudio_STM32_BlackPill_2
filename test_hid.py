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

# all_devices = hid.HidDeviceFilter().get_devices()
# if all_devices:
#     for device in all_devices:
#         try:
#             device.open()
#             print(f"Vendor Name: {device.vendor_name}, Product Name: {device.product_name}")
#             print(f"Vendor ID: {hex(device.vendor_id)}, Product ID: {hex(device.product_id)}")
#             print(f"Version Number: {hex(device.version_number)}")
#             print("-" * 30)
#         except Exception as e:
#             print(f"Could not open device: {e}")
#         finally:
#             device.close()
# else:
#     print("No HID devices found.")
