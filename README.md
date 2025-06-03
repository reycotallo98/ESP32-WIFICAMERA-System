# ESP32-WIFICAMERA-System

This proyect contains two arduino proyects, which are programmed for 3 ESP-32, one of them the server, and the other two the cameras whoes records.

## Requeriments

I used for my proyect this ESP-32 because it include a camera module, which cost 6€
(ESP32Cam)[https://es.aliexpress.com/item/1005003232704043.html?spm=a2g0o.order_list.order_list_main.12.43fc194dxoKu33&gatewayAdapt=glo2esp]

For the server you can use some ESP32 board wich need to have wifi like this, it cost around 3€:
[ESP32Server](https://es.aliexpress.com/item/1005004879572949.html?spm=a2g0o.detail.1000014.6.64a4111cMFW5Tq&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40050.281175.0&scm_id=1007.40050.281175.0&scm-url=1007.40050.281175.0&pvid=34d3b654-266d-4d7a-a376-415b3fe0a5a8&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.40050.281175.0,pvid:34d3b654-266d-4d7a-a376-415b3fe0a5a8,tpp_buckets:668%232846%238111%231996&pdp_ext_f=%7B%22sku_id%22%3A%2212000030924316155%22%2C%22sceneId%22%3A%2230050%22%7D&pdp_npi=3%40dis%21EUR%213.6%212.34%21%21%21%21%21%400b0a23a716780222693483418edd63%2112000030924316155%21rec%21ES%21744228666]

## Functionalities

- Server host index page, where allow us to see video record of cameras.
- We can control flash light of the esp32 throught a button on index page.
- It can grow, we can add more cameras, index page was programmed using bootstrap, which allow us to add more rows with more cams.
- The web server was updated to handle multiple clients at the same time.

## Instalation

1. Open arduino an load CAM project, you must change SSID and PASSWORD Strings on the proyect to yours, load on the arduino cam.
2. Open serial monitor on Arduino IDE, if all its ok, your cam ip will appear on the console. If you put this IP on your browser, you will see your cam working.
3. Now load Server project, change SSID and PASSWORD, now, got to html code and change the last octect of the ip on the src of the img tags, and the number in the function flash.
 ### like this
 for each row, u can use one cam...
 if your ip is 192.168.0.30, you will put on the img src 192.168.0.30, and in the flash(), you will put 30.
 
 
 ## How its shows
 
 After all, put on your browser 192.168.0.90 and you will see something like this
 ![image](https://user-images.githubusercontent.com/93315382/222963910-5a0393dd-4467-4786-843d-007647e84a99.png)
 
 You can flash the light, if you press the button flash.
 ![image](https://user-images.githubusercontent.com/93315382/222963941-c9604066-0be7-484f-a15d-4ef922bf8efe.png)

