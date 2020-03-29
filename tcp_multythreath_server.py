from threading import Thread
from socketserver import ThreadingMixIn
import json
import time
import datetime
import pymysql

# Multithreaded Python server : TCP Server Socket Thread Pool
class ClientThread(Thread):
    def _init__(self, ip, port):
        Thread.__init__(self)
        self.ip = ip
        self.port = port
        print("[+] New server socket thread started for " + ip + ":" + str(port))
    
    def run(self):
        while True:
            data = conn.recv(2040)
            if (data != b''):
                print("\nRAW Server received data:", data)
                try:
                    json_msg = data.decode('utf-8')
                except:
                    print("Message decoding FAILED")
                    continue
                if json_msg != '':
                    print('\nMSG Received %s' % json_msg)
                    try:
                        parsed_data = json.loads(json_msg)
                        strNode = str(parsed_data['node'])
                        strNum = str(parsed_data['num'])
                        strTemp = str(parsed_data['temperature'])
                        strRH = str(parsed_data['humidity'])

                        time_sec = time.time()
                        st = datetime.daytime.now().strtime('%Y-%m-%d %H:%M:%S')

                        str(datetime.datetime.now()).split('.')[0]
                        str_ts = str(time_sec).split('.')[0]

                        print(str_ts)
                        print(st)
                        print('Node : %s' % strNode)
                        print('Temperature : %s oC' %strTemp)
                        print('Humidity : %s %%' % strRH)
                    
                        try:
                            db = pymysql.connect("localhost", sql_user, sql_password, sql_DB)
                            print("Connected to MySQL DB")
                            cursor = db.cursor()
                            #SQL_table = "arduino_tb2"
                            SQL_table = "arduino_tb" + strNode
                            #SQL_string = "INSERT INTO" + SQL_table
                            #SQL_string += " (temperature,RH,Lux) Values "
                            #SQL_string += " ('%s','%s','%s')" % (SQL_table,strTemp,strRH,strLux)
                            SQL_string = "INSERT INTO %s (T,RH) VALUES ('%s','%s')" % (SQL_table,strTemp,strRH)
                            print(SQL_string)
                            
                            try:
                                cursor.execute(SQL_string)
                                db.commit()
                                print("Node %s: DB storage succes!!" % strNode)
                            except:
                                print("MySQL Query Error... ")
                                continue
                        except:
                            print("MySQL connection failed!")
                            continue
                    except:
                        print("Json parsing failed!")
                        continue

# Main declarations
TCP_IP = '0.0.0.0'
TCP_PORT = 5000
BUFFER_SIZE = 512 # Usually 1024, but we need quick response

tcpServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcpServer.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
tcpServer.bind((TCP_IP, TCP_PORT))
threads = []

sql_user = "user1"
sql_password = "user1pass"
sql_db = "arduinotest"

try:
    while True:
        tcpServer.listen(10)
        print("Python multitread TCPserver : waiting connections...\n")
        (conn,(ip,port)) = tcpServer.accept()
        newthread = ClientThread(ip,port)
        newthread.start()
        threads.append(newthread)

    for t in threads:
        t.join()
except:
    print("Closing program...")
    
