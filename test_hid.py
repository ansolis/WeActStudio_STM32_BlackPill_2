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
    device.close()
else:
    print("Device not found.")

if not devices:
    print("Can't find any non system HID device connected")
else:
    # search for our target usage
    for device in devices:
        try:
            device.open()
            # browse feature reports
            for report in device.find_feature_reports():
                print(report)
        finally:
            device.close()
