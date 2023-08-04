#!/usr/bin/env python3
import time
import serial
from flask import Flask, request, send_file

app = Flask(__name__)
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.reset_input_buffer()

@app.route('/', methods=["GET"])
def send():
    arg = request.args.get("arg")
    if arg != None: 
        data = send_serial(bytes(arg + "\n", 'utf-8'))
        return str(data)
    else: 
        return "No Argument provided"

@app.route('/client')
def index():
    return send_file("./index.html")

def send_serial(arg):
    ser.write(arg)
    return ser.readline().decode('utf-8').rstrip()


if __name__ == '__main__':

    print("Starting App")
    app.run( port="5000", host="0.0.0.0", debug=True)