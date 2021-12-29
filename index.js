// Default asynchronous request manager (classical AJAX method)
var xhttp = new XMLHttpRequest();
var time;
var buttons;

// ----------------------------------------------------------------------------
// Initialization on full loading of the HTML page
// ----------------------------------------------------------------------------

window.addEventListener('load', onLoad);

function onLoad(event) {
    initInfoDisplay();
    initTime();
    initButtons();
    updateButton();
    //updateStatus();
    Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
    Socket.onmessage = function(event) {
        processCommand(event);
    };
}

// ----------------------------------------------------------------------------
// Initialization of the info display
// ----------------------------------------------------------------------------

function initInfoDisplay() {
    nome = document.getElementById('nome');
    ssid = document.getElementById('ssid');
    vers = document.getElementById('versione');
    tempo = document.getElementById('nome');
    rssi = document.getElementById('rssi');
    pc = document.getElementById('rssiPer');
}
// ----------------------------------------------------------------------------
// Initialization of the current time display
// ----------------------------------------------------------------------------
function initTime() {
    time = document.getElementById('time');
    setInterval(updateTime, 1000);
}

function updateTime() {
    let now = new Date();
    let h = now.getHours();
    let m = now.getMinutes();
    let s = now.getSeconds();
    time.value = `${normalize(h)}:${normalize(m)}:${normalize(s)}`;
}

function normalize(digit) {
    return (digit < 10 ? '0' : '') + digit;
}


// ----------------------------------------------------------------------------
// Initialization and handling of the ESP32 control buttons
// ----------------------------------------------------------------------------

function initButtons() {
    buttons = document.querySelectorAll("button[id^='btn'][id$='menu']");
    buttons[0].addEventListener('click', bt1);
    buttons[1].addEventListener('click', bt2);
    buttons[2].addEventListener('click', bt3);
    buttons[3].addEventListener('click', bt4);
    buttons[4].addEventListener('click', bt5);
    buttons[5].addEventListener('click', bt6);
    buttons[6].addEventListener('click', bt7);
    buttons[7].addEventListener('click', bt8);
    buttons[8].addEventListener('click', bt9);
}

// Btn event manager
// ---------------------------
function bt1(event) {
    const msg = {
        type: 'bt',
        value: 1
    };
    Socket.send(JSON.stringify(msg));
}

function bt2(event) {
    const msg = {
        type: 'bt',
        value: 2
    };
    Socket.send(JSON.stringify(msg));
}

function bt3(event) {
    const msg = {
        type: 'bt',
        value: 3
    };
    Socket.send(JSON.stringify(msg));
}

function bt4(event) {
    const msg = {
        type: 'bt',
        value: 4
    };
    Socket.send(JSON.stringify(msg));
}

function bt5(event) {
    const msg = {
        type: 'bt',
        value: 5
    };
    Socket.send(JSON.stringify(msg));
}

function bt6(event) {
    const msg = {
        type: 'bt',
        value: 6
    };
    Socket.send(JSON.stringify(msg));
}

function bt7(event) {
    const msg = {
        type: 'bt',
        value: 7
    };
    Socket.send(JSON.stringify(msg));
}

function bt8(event) {
    const msg = {
        type: 'bt',
        value: 8
    };
    Socket.send(JSON.stringify(msg));
}

function bt9(event) {
    //reset
    const msg = {
        type: 'btreset',
        value: 0
    };
    Socket.send(JSON.stringify(msg));
}
//---------------------------------
// WEBSOCKET MESSAGE MANAGER
//---------------------------------
function processCommand(event) {
    const obj = JSON.parse(event.data);
    const type = obj.type;
    if (type.localeCompare('bt_esp') == 0) {
        //ESP ha ricevuto una pressione tasto pulsante
        //e risponde con lo stato del pulsante aggiornato
        //JS cambia il colore del testo in accordo
        if (obj.value == 1) {
            buttons[obj.gr].classList.add("button3");
        } else {
            buttons[obj.gr].classList.remove("button3");
        }
        console.log('Stato pulsante cambiato: ' + obj.gr + ' -> ' + obj.value);
    } else if (type.localeCompare('rssi_esp') == 0) {
        //ogni secondo viene aggiornato il RSSI dal ESP
        rssi.value = obj.rssi;
        pc.value = obj.rssiPer;
    } else if (type.localeCompare('tempo_esp') == 0) {
        //ogni minuto viene aggiornato il tempo di accensione dal ESP
        nome.value = obj.tempo;
    } else if (type.localeCompare('resetP_esp') == 0) {
        //reset pulsant
        for (let index = 0; index < buttons.length; index++) {
            buttons[index].classList.remove("button3")
        }
    } else if (type.localeCompare('conn_esp') == 0) {
        //Solo  ad una nuova connessione viene mandato tutto
        //il pacchetto dati e solo allo specifico client
        vers.value = obj.vers;
        ssid.value = obj.ssid;
        const aa = obj.puls;
        for (let index = 0; index < aa.length; index++) {
            const element = aa[index];
            if (aa[index] == 1) {
                buttons[index].classList.add("button3")
            } else {
                buttons[index].classList.remove("button3")
            }
        }
    }
}
//-----------------------------
// BUTTONS LABEL MANAGER
//-----------------------------
const updateButton = () => {
    //questo scrive i nomi dei pulsanti dal file pulsName.php
    fetch('http://www.cadolabiot.altervista.org/100/pulsName.php')
        .then(res => res.json())
        .then(val => {
            const aa = val.puls;
            for (let index = 0; index < aa.length; index++) {
                const el = aa[index];
                buttons[index].textContent = el;
            }
        })
        .catch(err => {
            console.error('Error getting status', err);
        });
};
//---------------------------------
//IL VECCHIO SISTEMA FETCH E' ABBANDONATO
//---------------------------------
// const updateStatus = () => {
//     //fetch(window.location.href + 'status')
//     fetch('/status')
//     .then(res => res.json())

//     .then(val => {
//       nome.value = val.tempo;
//       vers.value = val.vers;

//       ssid.value = val.ssid;
//       rssi.value =val.rssi;
//       pc.value = val.rssiPer;
//       const aa=val.puls;
//       for (let index = 0; index < aa.length; index++) {
//           const element = aa[index];
//           if(aa[index]==1) {
//               buttons[index].classList.add("button3")
//           }else{
//               buttons[index].classList.remove("button3")
//           }
//       }
//       setTimeout(updateStatus, 1000);
//     }).catch(err => {
//       console.error('Error getting status', err);
//       setTimeout(updateStatus, 1000);
//     });
//   };

// -------------------------------------------------------
// AJAX requests
// -------------------------------------------------------

// Using standard vanilla XHR (XMLHttpRequest method)
// @see https://www.w3schools.com/xml/ajax_xmlhttprequest_send.asp

// function xhrRequest(path, callback) {

//     xhttp.onreadystatechange = function() {
//         if (this.readyState == 4 && this.status == 200) {
//             // callback is optional!
//             typeof callback === 'function' && callback(this.responseText);
//         }
//     };

//     xhttp.open('GET', path, true);
//     xhttp.send();
// }