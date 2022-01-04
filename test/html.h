/*
 * HTML
 */
#pragma once
#ifndef _html_h
#define _html_h
//String p = "";
//const char* page ="<!DOCTYPE html><html><head> <title id='title'>CADOLAB100</title> <meta name='apple-mobile-web-app-capable' content='yes'> <meta name='apple-mobile-web-app-status-bar-style' content='default'> <meta name='viewport' content='width=device-width, user-scalable=no'> <link rel='stylesheet' href='http://www.cadolabiot.altervista.org/100/style.php'></head><body> <div > <h1 class='inset'>CADOLAB100</h1> <div class='buttons'> <button id='btn1menu' ></button> <button id='btn2menu'></button> <button id='btn3menu'></button> <button id='btn4menu'></button> <button id='btn5menu'></button> <button id='btn6menu'></button><button id='btn7menu'></button><button id='btn8menu'></button> <button id='btn9menu'></button> </div><div class='parameters'> <div class='display'> <label class='inset' for='time'>TIME</label> <input type='text' id='time' readonly > </div><div class='display'> <label class='inset' for='nome'>RUNNING BY</label> <input type='text' id='nome' readonly> </div><div class='display'> <label class='inset' for='versione'>VERSIONE</label> <input type='text' id='versione' value='WEB' readonly> </div><div class='display'> <label class='inset' for='ssid'>SSID</label> <input type='text' id='ssid' readonly> </div><div class='display'> <label class='inset' for='rssi'>RSSI</label> <input type='text' id='rssi' readonly> </div><div class='display'> <label class='inset' for='rssiPer'>RSSI PER100</label> <input type='text' id='rssiPer' readonly> </div></div></div></body><script src='http://www.cadolabiot.altervista.org/100/indexwsjs.php'></script></html>";
//int refreshPage = 3;
//const char* intestazioneRoot ="<!DOCTYPE html><html><head>";
//const char* intestazionePuls ="<!DOCTYPE html><html><head><meta http-equiv=\"refresh\" content=\"0;url=/\">";
// const char* intestazione ="<!DOCTYPE html><html><head><title>CADOLAB100</title><meta name='description' content='CADOLAB100'/><meta name='apple-mobile-web-app-capable' content='yes'><meta name='apple-mobile-web-app-status-bar-style' content='default'><meta name='viewport' content='width=device-width, user-scalable=no'>";
// const char* style = "<style type='text/css'> html{height: 100%;}table{border: 1px solid gray; border-collapse: collapse; margin: 1em 0;}body{-webkit-background-size: 100% 21px;}.view{min-height: 100%; overflow: auto;}.header-wrapper{height: 44px; font-weight: bold; text-shadow: rgba(0, 0, 0, 0.7) 0 -1px 0; border-top: solid 1px rgba(255, 255, 255, 0.6); border-bottom: solid 1px rgba(0, 0, 0, 0.6); color: #fff; background-color: #808080; background-image: -webkit-gradient(linear, left top, left bottom, from(rgba(255, 255, 255, .4)), to(rgba(255, 255, 255, .05))), -webkit-gradient(linear, left top, left bottom, from(transparent), to(rgba(0, 0, 64, .1))); background-repeat: no-repeat; background-position: top left, bottom left; -webkit-background-size: 100% 21px, 100% 22px; -webkit-box-sizing: border-box;}.group-wrapper{margin: 9px;}table{border: 1px solid gray; border-collapse: collapse; margin: 1em 0;}h1, input, button{font-size: 100%; text-align: center;}.dim{border: 1px solid #f0731c; width: 100%; text-align: center;}.pulsante{width: 60px; height: 60px; border: 1px solid #000; margin: 5px;}.button{background-color: #4CAF50; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px;}.button2{background-color: #008CBA;}/* Blue */ .button3{background-color: #f44336;}/* Red */ .button4{background-color: #e7e7e7; color: black;}/* Gray */ .button5{background-color: #555555;}</style>";
// const char* header = "</head><body> <div class='view'><div class='header-wrapper'><h1>CADOLAB100</h1></div><div class='group-wrapper'><h2>ABITAZIONE</h2>";
// const char* nom ="<table cellspacing='2' cellpadding='10' border='2'><tr><td>NOME</td><td id='nome'>";
// const char* prog ="</td></tr><tr><td>PROGETTO</td><td id='progetto'>";
// const char* vers = "</td></tr><tr><td>VERSIONE</td><td id='vers'>";
// const char* ss = "</td></tr><tr><td>WIFI SSID</td><td id='ssid'>";
// const char* rs = "</td></tr><tr><td>RSSI</td><td id='rssi'>";
// const char* rsper = "</td></tr><tr><td>RSSI</td><td id='rssiPer'>";
// const char* fineTabella ="</td></tr></table></div></div></body>";
// //const char* finePagina ="<table cellspacing='2' cellpadding='10' border='2'><tr><td>NOME</td><td id='nome'></td></tr><tr><td>PROGETTO</td><td id='progetto'></td></tr><tr><td>VERSIONE</td><td id='vers'></td></tr><tr><td>WIFI SSID</td><td id='ssid'></td></tr><tr> <td>RSSI</td><td id='rssi'></td></tr><tr><td>RSSI</td><td id='rssiPer'></td></tr></table></div></div></body>";
// //const char* script ="<script>const nome=document.getElementById('nome'); const prog=document.getElementById('progetto'); const versEl=document.getElementById('vers'); const ssid=document.getElementById('ssid'); const rssi=document.getElementById('rssi'); const pc=document.getElementById('rssiPer'); const buttons=document.querySelectorAll( \"button[id^='button'][id$='menu']\" ); const updateStatus=()=>{fetch('/status') .then(res=> res.json()) .then(val=>{nome.innerHTML=val.nome; versEl.innerHTML=val.vers; prog.innerHTML=val.prog; ssid.innerHTML=val.ssid; rssi.innerHTML=val.rssi; pc.innerHTML=val.rssiPer; aa=val.puls; for (let index=0; index < aa.length; index++){const element=aa[index]; if(element){buttons[index].classList.replace(\"button4\",\"button3\")}else{buttons[index].classList.replace(\"button3\",\"button4\")}}setTimeout(updateStatus, 1000);}).catch(err=>{console.error('Error getting status', err); setTimeout(updateStatus, 1000);});};updateStatus();</script></html>";
// const char* script="<script>const ssid=document.getElementById('ssid'); const rssi=document.getElementById('rssi'); const pc=document.getElementById('rssiPer'); const buttons=document.querySelectorAll( \"button[id^='button'][id$='menu']\" ); const updateStatus=()=>{fetch('/status') .then(res=> res.json()) .then(val=>{ssid.innerHTML=val.ssid; rssi.innerHTML=val.rssi; pc.innerHTML=val.rssiPer; aa=val.puls; for (let index=0; index < aa.length; index++){const element=aa[index]; if(element){buttons[index].classList.replace(\"button4\",\"button3\")}else{buttons[index].classList.replace(\"button3\",\"button4\")}}setTimeout(updateStatus, 1000);}).catch(err=>{console.error('Error getting status', err); setTimeout(updateStatus, 1000);});};updateStatus();</script></html>";
#endif