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