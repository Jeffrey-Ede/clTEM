/* Toggle between adding and removing the "responsive" class to topnav when the user clicks on the icon */
function toggleMenu() {
    document.getElementsByClassName("topnav")[0].classList.toggle("responsive");
}

function closeMenu() {
    document.getElementsByClassName("topnav")[0].classList.toggle("responsive", false);
}

function toggleDropdown() {
    document.getElementsByClassName("dropdown-content")[0].classList.toggle("displayed");
    document.getElementsByClassName("dropdown")[0].classList.toggle("expanded");
}

// https://stackoverflow.com/questions/23885255/how-to-remove-ignore-hover-css-style-on-touch-devices
function watchForHover() {
    var hasHoverClass = false;
    var container = document.body;
    var lastTouchTime = 0;

    function enableHover() {
        // filter emulated events coming from touch events
        if (new Date() - lastTouchTime < 500) return;
        if (hasHoverClass) return;

        container.className += ' hasHover';
        hasHoverClass = true;
    }

    function disableHover() {
        if (!hasHoverClass) return;

        container.className = container.className.replace(' hasHover', '');
        hasHoverClass = false;
    }

    function updateLastTouchTime() {
        lastTouchTime = new Date();
    }

    document.addEventListener('touchstart', updateLastTouchTime, true);
    document.addEventListener('touchstart', disableHover, true);
    document.addEventListener('mousemove', enableHover, true);

    enableHover();
}


function colorTaps() {
     var ac = document.getElementsByClassName('topnav')
    for (var i = 0; i < ac.length; i++) {
      var a = ac[i].getElementsByTagName('a');
      for (var j = 0; j < a.length; j++) {
        a[j].ontouchstart = function(){this.classList.toggle("touched", true);} // on tapping
        a[j].ontouchend = function(){this.classList.toggle("touched", false);} // on releasing
        a[j].ontouchmove = function(){this.classList.toggle("touched", false);} // on moving (i.e. we arent pressing)
      }
    }
}


function watchForResize() {

    // https://stackoverflow.com/questions/11309859/css-media-queries-and-javascript-window-width-do-not-match
    function viewport() {
        var e = window, a = 'inner';
        if (!('innerWidth' in window )) {
            a = 'client';
            e = document.documentElement || document.body;
        }
        return { width : e[ a+'Width' ] , height : e[ a+'Height' ] };
    }

    var lastSize = 0;
    function updateResize() {
        var w = viewport(); 
        if (w.width > 680) {
            if (lastSize <= 680) {
                document.getElementsByClassName("dropdown-content")[0].classList.toggle("displayed", false);
                document.getElementsByClassName("dropdown")[0].classList.toggle("expanded", false);
                closeMenu();
            }

            var ac = document.getElementsByClassName('dropbtn')
            for (var i = 0; i < ac.length; i++) {
                ac[i].onclick = function(){}
            }

        } else {
            var ac = document.getElementsByClassName('dropbtn')
            for (var i = 0; i < ac.length; i++) {
            ac[i].onclick = function(){return false;}
            }
        }

        lastSize = w.width;
    }

    window.addEventListener("resize", updateResize, false);

    updateResize();
}