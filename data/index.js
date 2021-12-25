/**
 * ----------------------------------------------------------------------------
 * ESP32 Web Controlled Thermostat
 * ----------------------------------------------------------------------------
 * Author: Stéphane Calderoni
 * Date:   April 2020
 * ----------------------------------------------------------------------------
 * This project is a response to a request made on the RNT Lab forum:
 * https://rntlab.com/question/java-script-code-to-refresh-home-page-only-once/
 * ----------------------------------------------------------------------------
 */

// ----------------------------------------------------------------------------
// Global constants
// ----------------------------------------------------------------------------

// Periodic temperature reading delay
const temperatureCaptureTime = 2000; // 2 seconds (in milliseconds)

// ----------------------------------------------------------------------------
// Global variables
// ----------------------------------------------------------------------------

// Default asynchronous request manager (classical AJAX method)
var xhttp = new XMLHttpRequest();

/**
 * We will need to read some data or update some elements of the HTML page.
 * So we need to define variables to reference them more easily throughout 
 * the program.
 */

// Current temperature display screen
// ----------------------------------

//var screen;      // Container
//var temperature; // HTML element that incorporates the current temperature value
//var unit;        // HTML element that incorporates the display of the temperature reading unit (°C)

// Input fields for temperature limits
// -----------------------------------

//var upper;
//var lower;

// Current time display
// --------------------

var time;

// ESP32 control buttons
// ---------------------

var buttons ;

// ----------------------------------------------------------------------------
// Initialization on full loading of the HTML page
// ----------------------------------------------------------------------------

window.addEventListener('load', onLoad);

function onLoad(event) {
    initInfoDisplay();
    initTime();
    //initThresholds();
    initButtons();
    updateStatus();
    showPanel();
}

// ----------------------------------------------------------------------------
// Progressive appearance of the control panel when everything is ready
// ----------------------------------------------------------------------------

function showPanel() {
    let panel = document.getElementById('panel');
    panel.classList.add('showing');
    panel.addEventListener('animationend', () => { panel.style.opacity = 1; });
}

// ----------------------------------------------------------------------------
// Initialization of the current temperature display
// ----------------------------------------------------------------------------

function initInfoDisplay() {
    nome    = document.getElementById('nome');
   
    versEl  = document.getElementById('vers');
    ssid    = document.getElementById('ssid');
    rssi    = document.getElementById('rssi');
    pc      = document.getElementById('rssiPer');
}

// ----------------------------------------------------------------------------
// Initialization of the current time display
// ----------------------------------------------------------------------------

function initTime() {
    time = document.getElementById('time');
    
    // a timing event manager is initialized
    // which must be triggered every second to refresh
    // the display of the current time
    setInterval(updateTime, 1000);
}

function updateTime() {
    let now    = new Date();
    let h      = now.getHours();
    let m      = now.getMinutes();
    let s      = now.getSeconds();
    time.value = `${normalize(h)}:${normalize(m)}:${normalize(s)}`;
}

function normalize(digit) {
    return (digit < 10 ? '0' : '') + digit;
}

// ----------------------------------------------------------------------------
// Initialization and control of the input fields for temperature thresholds
// ----------------------------------------------------------------------------

// function initThresholds() {
//     lower = document.getElementById('lower');
//     upper = document.getElementById('upper');
// }

// Event managers related to the entry of new temperature thresholds
// -----------------------------------------------------------------

// Once the entry is complete
// --------------------------

/**
 * Here we must make sure that the temperature thresholds have been entered correctly:
 * the user may have inverted the min and max when entering them, in which case they
 * must be put back in the right order.
 * 
 * Once this check has been made, the display screen of the current temperature is
 * refreshed to take into account the new thresholds, and change the display colour
 * if necessary.
 * 
 * Finally, the new thresholds are transmitted to the ESP32 to be saved in the EEPROM.
 */

// function saveThresholds() {
//     let low     = Number.parseFloat(lower.value);
//     let upp     = Number.parseFloat(upper.value);
//     let new_low = Math.min(low, upp);
//     let new_upp = Math.max(low, upp);

//     // in case the thresholds have been reversed,
//     // or if the user has entered too many decimal places
//     lower.value = new_low.toFixed(1);
//     upper.value = new_upp.toFixed(1);

//     // then temperature display color may change...
//     setTemperature(temperature.innerText);

//     // finally, the new thresholds are sent to the ESP32 for storage in the EEPROM:
//     // asynchronous call of the remote routine with the classical method
//     xhrRequest(`/savethresholds?lower=${new_low}&upper=${new_upp}`);

//     // for a more modern method, you can instead call this manager:
//     // asyncAwaitRequest(`/savethresholds?lower=${new_low}&upper=${new_upp}`);
// }

// // While the user is entering a value
// // ----------------------------------

// function digitOnly(event) {
//     if (event.keyCode == 13) {
//         saveThresholds();
//         return false;
//     }
//     return /[\d-\.]/.test(event.key);
// }

// ----------------------------------------------------------------------------
// Initialization and handling of the ESP32 control buttons
// ----------------------------------------------------------------------------

function initButtons() {
    buttons = document.querySelectorAll( "button[id^='btn'][id$='menu']" );
    buttons[0].addEventListener('click', bt1);
    buttons[1].addEventListener('click', bt2);
    buttons[2].addEventListener('click', bt3);
    buttons[3].addEventListener('click', bt4);
    buttons[4].addEventListener('click', bt5);
    buttons[5].addEventListener('click', bt6);
    buttons[6].addEventListener('click', bt7);
    buttons[7].addEventListener('click', bt8);
    //btnReboot.addEventListener('click', onReboot);
}

// Factory reset event manager
// ---------------------------
function bt1(event) {
    xhrRequest('/q');
}
function bt2(event) {
    xhrRequest('/w');
}
function bt3(event) {
    xhrRequest('/e');
}
function bt4(event) {
    xhrRequest('/r');
}
function bt5(event) {
    xhrRequest('/t');
}
function bt6(event) {
    xhrRequest('/y');
}
function bt7(event) {
    xhrRequest('/u');
}
function bt8(event) {
    xhrRequest('/i');
}
// function onDefault(event) {
//     // asynchronous call of the remote routine with the classical method
//     xhrRequest('/reset');

//     // for a more modern method, you can instead call this manager:
//     // asyncAwaitRequest('/reset');

//     // refreshes all temperature displays
//     lower.value = Number.parseFloat(lower.dataset.min).toFixed(1);
//     upper.value = Number.parseFloat(upper.dataset.max).toFixed(1);
//     setTemperature(temperature.innerText);
// }

// Event manager for restarting ESP32
// ----------------------------------

// function onReboot(event) {
//     // sends reboot command to the ESP32
//     xhrRequest('/reboot');
// }

// ----------------------------------------------------------------------------
// Initialization and handling of the temperature sensor
// ----------------------------------------------------------------------------

// function initProbe() {
//     setTemperature(temperature.innerText);
//     setInterval(getTemperature, temperatureCaptureTime);
// }

// Sending the current temperature reading request
// -----------------------------------------------

// function getTemperature() {
//     /**
//      * a `setTemperature()` callback function is designated in the following
//      * to update the temperature display when the ESP32 has transmitted the response.
//      */

//     // asynchronous call of the remote routine with the classical method
//     xhrRequest('/temp', (temp) => { setTemperature(temp); });

//     // for a more modern method, you can instead call this manager:
//     // asyncAwaitRequest('/temp', (temp) => { setTemperature(temp); });
// }
const updateStatus = () => {
    fetch('/status')
    .then(res => res.json())
    
    .then(val => {
      nome.value = val.nome;
      versEl.value = val.vers;
      
      ssid.value = val.ssid;
      rssi.value =val.rssi;
      pc.value = val.rssiPer;
      aa=val.puls;
      for (let index = 0; index < aa.length; index++) {
          const element = aa[index];
          if(aa[index]==1) {
              buttons[index].classList.add("button3")
          }else{
              buttons[index].classList.remove("button3")
          }
      }
      setTimeout(updateStatus, 1000);
    }).catch(err => {
      console.error('Error getting status', err);
      setTimeout(updateStatus, 1000);
    });
  };
// Updating the display when the value read on the sensor is received
// ------------------------------------------------------------------

// function setTemperature(temp) {
    
//     if (temp == 'Error') {
//         temperature.innerText = temp;
//         unit.style.display = 'none';
//         screen.className = 'error';
//     } else {

//         let low = Number.parseFloat(lower.value);
//         let upp = Number.parseFloat(upper.value);
//         let t   = Number.parseFloat(temp).toFixed(1);

//         if (t < low) {
//             screen.className = 'cold';
//         } else if (t > upp) {
//             screen.className = 'hot';
//         } else {
//             screen.className = '';
//         }

//         temperature.innerText = t;
//         unit.style.display = 'inline';
//     }
// }

// -------------------------------------------------------
// AJAX requests
// -------------------------------------------------------

// Using standard vanilla XHR (XMLHttpRequest method)
// @see https://www.w3schools.com/xml/ajax_xmlhttprequest_send.asp

function xhrRequest(path, callback) {
    
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            // callback is optional!
            typeof callback === 'function' && callback(this.responseText);
        }
    };

    xhttp.open('GET', path, true);
    xhttp.send();
}

// Using Async/Await Promises
// @see: https://medium.com/@mattburgess/how-to-get-data-with-javascript-in-2018-f30ba04ad0da

// function asyncAwaitRequest(path, callback) {
//     (async () => {
//         let response = await fetch(path);
//         let temp     = await response.text();
//         // callback is optional!
//         typeof callback === 'function' && callback(temp);
//     })();
// }