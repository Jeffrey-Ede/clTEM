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

// watchForHover();