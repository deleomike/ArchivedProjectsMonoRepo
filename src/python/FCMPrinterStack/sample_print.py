# Example of getting a list of printers
import cups

conn = cups.Connection()
printers = conn.getPrinters ()

for printer in printers:
    print(printer, printers[printer]["device-uri"])