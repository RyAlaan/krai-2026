import socket
import struct
import math
from time import sleep
from pySerialTransfer import pySerialTransfer as txfer

# Konfigurasi UDP
client_ip = "10.146.23.86"  # IP client (Raspberry Pi)/ cek pake "ipconfig" di cmd. Ubah jadi 0.0.0.0 agar tidak perlu setting ulang
client_port = 4444  # Port client

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((client_ip, client_port))
print(f"Client terhubung di {client_ip}:{client_port}, siap menerima data...")

def controlESP():
    global cmd
    if CROSS:
        cmd = 'a'
    elif CIRCLE:
        cmd = 'b'
    elif SQUARE:
        cmd = 'c'
    elif TRIANGLE:
        cmd = 'd'
    elif SELECT:
        cmd = 'e'
    elif START:
        cmd = 'f'
    elif L1:
        cmd = 'g'
    elif R1:
        cmd = 'h'
    elif R2:
        cmd = 'i'
    elif L2:
        cmd = 'j'
    else:
        cmd = 'z'
    
def controlSTM():
    global vx, vy, wr, cmd
    theta = math.atan2(LY, LX)
    vx = math.cos(theta) if LX < -50 or LX > 50 else float(RIGHT) - float(LEFT)
    vy = math.sin(theta) if LY < -50 or LY > 50 else float(UP) - float(DOWN)
    wr = -1.0 if RX < -50 else 1.0 if RX > 50 else 0.0

    if CROSS:
        cmd = 'a'
    elif CIRCLE:
        cmd = 'b'
    else:
        cmd = 'z'


def transmitStm():
    sendSizeSTM32 = 0
    sendSizeSTM32 = link1.tx_obj(cmd, start_pos=sendSizeSTM32)
    sendSizeSTM32 = link1.tx_obj(vx, start_pos=sendSizeSTM32)
    sendSizeSTM32 = link1.tx_obj(vy, start_pos=sendSizeSTM32)
    sendSizeSTM32 = link1.tx_obj(wr, start_pos=sendSizeSTM32)
    link1.send(sendSizeSTM32)

# def transmitEsp():
#     sendSizeESP32 = 0
#     # sendSizeESP32 = link2.tx_obj(cmd, start_pos=sendSizeESP32)
#     # link2.send(sendSizeESP32)

def receiveStm():
    global Vfr, Vfl, Vbl,Vbr
    recSize = 0
    Vfr = link1.rx_obj(obj_type='f', start_pos=recSize)
    recSize += txfer.STRUCT_FORMAT_LENGTHS['f']
    Vfl = link1.rx_obj(obj_type='f', start_pos=recSize)
    recSize += txfer.STRUCT_FORMAT_LENGTHS['f']
    Vbl = link1.rx_obj(obj_type='f', start_pos=recSize)
    recSize += txfer.STRUCT_FORMAT_LENGTHS['f']
    Vbr = link1.rx_obj(obj_type='f', start_pos=recSize)
    recSize += txfer.STRUCT_FORMAT_LENGTHS['f']
# def receiveEsp():
#     global Vroll1, Vroll2
#     recSize = 0
#     Vroll1 = link2.rx_obj(obj_type='f', start_pos=recSize)
#     recSize += txfer.STRUCT_FORMAT_LENGTHS['f']
#     Vroll2 = link2.rx_obj(obj_type='f', start_pos=recSize)
#     recSize += txfer.STRUCT_FORMAT_LENGTHS['f']


# Inisialisasi nilai awal
Vfr = Vfl = Vbl = Vbr = Vroll1 = Vroll2 = 0.0

try:
    link1 = txfer.SerialTransfer('COM4') #/dev/ttyUSB0  || /dev/serial0
    # link2 = txfer.SerialTransfer('COM12') #/dev/ttyUSB0  || /dev/serial0
    link1.open()
    # link2.open()
    sleep(2)

    while True:
        data, addr = sock.recvfrom(22)
        if len(data) == 22:
            # Memecah data menggunakan struct.unpack
            unpacked_data = struct.unpack("bbbb??????????????????", data)
            # Mapping data
            LX, LY, RX, RY = unpacked_data[:4] #mengambil 4 elemen pertama
            L2, R2, CROSS, CIRCLE, SQUARE, TRIANGLE, SELECT, HOME, START, L3, R3, L1, R1, UP, DOWN, LEFT, RIGHT, PAD = unpacked_data[4:] #mengambil elemend indeks ke 4 sampai akhir

            # Print data yang diterima
            # print(f"LX ={LX}|LY ={LY}|RX={RX}|RY={RY}|L2={L2}|R2={R2}|CROSS={CROSS}|CIRCLE={CIRCLE}|SQUARE={SQUARE}"
            #       f"|TRIANGLE={TRIANGLE}|SELECT={SELECT}|HOME={HOME}|START={START}|L3={L3}|R3={R3}|L1={L1}" 
            #       f"|R1={R1}|UP={UP}|DOWN={DOWN}|LEFT={LEFT}|RIGHT={RIGHT}|PAD={PAD}")
        else:
            LX = LY = RX = RY = L2 = R2 = CROSS = CIRCLE = SQUARE = TRIANGLE = SELECT = HOME = START = L3 = R3 = L1 = R1 = UP = DOWN = LEFT = RIGHT = PAD = 0
            print("Data yang diterima tidak sesuai ukuran.")

        controlSTM()
        # controlESP()

        transmitStm()
        # transmitEsp()        

        if link1.available():
            receiveStm()
        # if link2.available():
        #     receiveEsp()


        print(f"Analog DS4: LX={LX:4d} | LY={LY:4d} | RX={RX:4d} | RY={RY:4d} ||  Kirim ke STM: vx={vx:.2f} | vy={vy:.2f} | wr={wr:.2f} | cmd={cmd}")
        # print('{} | {} | {} | {} | {} | {}'.format(Vfr, Vfl, Vbl, Vbr, Vroll1, Vroll2))
            
        
except KeyboardInterrupt:
    link1.close()
    # link2.close()
finally:
    sock.close()