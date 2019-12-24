import serial
import MySQLdb
dbConn = MySQLdb.connect("localhost","root","1","datn") or die ("could not connect to database")
cursor = dbConn.cursor()
print "Network MySQL..."
try:
  sql="DROP TABLE IF EXISTS datas"
  cursor.execute(sql)
  dbConn.commit()
except:
  dbConn.rollback()
  print"Deleted TABLE..."
sql=""" CREATE TABLE datas (STT int(5) primary key auto_increment,
            H_R int(5) not null,
            SpO2 int(5) not null,
            Date_Time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            )"""
cursor.execute(sql)
dbConn.commit()
print"CREATED TABLE NEW..."

device = '/dev/ttyUSB0' 
try:
  print "Trying...",device
  arduino = serial.Serial(device, 115200)
except:
  print "Failed to connect Serial",device
  cursor = dbConn.cursor()
while True:
  try:
    data = arduino.readline() 
    data = data.replace("\r\n", ""); 
    data = data.split(" ")
    try: 
      heartRate = int(data[0])
      SpO2 = int(data[1])
      sql = "INSERT INTO datas (H_R,SpO2) VALUES (%d, %d)" %(heartRate, SpO2)
      print sql
      cursor.execute(sql)
      dbConn.commit()
    except error:
      print error
      print "Error Update"  
  except:
    print " Network failed data from Arduino!"