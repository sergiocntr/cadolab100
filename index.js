// Default asynchronous request manager (classical AJAX method)
var xhttp = new XMLHttpRequest();
var time;
var buttons ;

// ----------------------------------------------------------------------------
// Initialization on full loading of the HTML page
// ----------------------------------------------------------------------------

window.addEventListener('load', onLoad);

function onLoad(event) {
    initInfoDisplay();
    initTime();
    initButtons();
    updateStatus();
  
}

// ----------------------------------------------------------------------------
// Initialization of the current temperature display
// ----------------------------------------------------------------------------

function initInfoDisplay() {
   // nome    = document.getElementById('nome');
    ssid    = document.getElementById('ssid');
    vers  = document.getElementById('versione');
    tempo   = document.getElementById('nome');
    rssi    = document.getElementById('rssi');
    pc      = document.getElementById('rssiPer');
}
// ----------------------------------------------------------------------------
// Initialization of the current time display
// ----------------------------------------------------------------------------
function initTime() {
    time = document.getElementById('time');
    
    
    //setInterval(updateTime, 1000);
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
    buttons[7].addEventListener('click', bt9);
    buttons[8].addEventListener('click', bt8);
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
function bt9(event) {
  xhrRequest('/reset');
}
const updateStatus = () => {
    fetch(window.location.href + 'status')
    .then(res => res.json())
    
    .then(val => {
      nome.value = val.nome;
      vers.value = val.vers;
      
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
