# FCM Printer Stack

The printer stack is intended to sit in the print room with ethernet connections to all printers. It is the manager that:
1. receives a print job 
2. determines the correct printer to use
3. Handles the sending of the
   1. Card Stock Job (Card itself)
   2. Envelope
   3. Info Sheet For IDing the card
4. Notifies by email or ticket that the job is done

After the print has completed, the info sheet will indicate if money (or a gift card) needs to be included). Later on down the line, this stack could also accomodate 3d printing.

The stack is essentially a backend API server that can be communicated with from the FCM main schedule keeper server.

## Deployment

Just python right now
```bash
python3 -m venv env
. ./env/bin/activate
pip install -r requirements.txt
uvicorn printpy.main:app --reload
```