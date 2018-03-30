# luxmeter

โปรเจควัดค่าแสงสว่างแล้วส่งขึ้น netpie 

## รายละเอียดระบบ

โปรเจคจะมีอ่านค่าเซนเซอร์จาก BH1750 เพื่อรับค่าแสงสว่างแล้วส่งขึ้น netpie แต่จะมีเงื่อนไขว่า ถ้าความสว่างน้อยกว่า 20000 lux ก็จะเปิดไฟ
ถ้ามีการเปิดไฟ จะส่งสถานะการเปิดไฟขึ้นไปแสดงที่ netpie ด้วย

### การตั้งค่าต่างๆ และสิ่งที่ต้องใข้

ไลบรารีที่ต้องใช้
1.netpie microgear

พารามิเตอร์ต่างๆ ในการกำหนดให้ระบบทำงานอยู่ทางตอนต้นของโค้ด

```
#define APPID   "xxxxxxx"   //หมายเลข appid ของท่านที่สร้างใน netpie
#define KEY     "xxxxxxx"   //key ที่สร้างขึ้น ใน APPID
#define SECRET  "xxxxxxx"   //secrate ที่ได้จากการสร้าง key

#define ALIAS   "luxmeter"                // ชื่ออุปกรณ์ของท่านที่จะให้ปรากฏใน netpie
#define TargetWeb "HTML_web"
#define LIGHT_STATUS "HTML_light" 

// --------------------------------------------------------------------------------------

//ขา รีเลย์ ต่างที่ต่อ ในที่นี้ใช้การอ้างอิงด้วย nodemcu เป็นหลัก
#define LIGHT1 D7 

```
### การติดตั้ง

ดาวน์โหลดโค้ดแล้วคอมพายล์ด้วย Ardunio IDE

## สร้างด้วย

* [Ardunio 1.8.3](https://www.arduino.cc/en/main/software) - ดาวน์โหลดเวอร์ชั่นล่าสุดได้ที่นี่
* [Microgear Lirary](https://github.com/netpieio/microgear-esp8266-arduino) - ไลบรารีสำหรับการเชื่อมต่อ netpie 

## ผู้เขียน

* **Suphanut Thanyaboon** - *ผู้ริเริ่ม* - [maskung](https://github.com/maskung)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
