onload = () => {
    const selMac = document.getElementById("selMac");
    const macInput = document.getElementById("mac");

    for (let el of document.querySelectorAll("select"))
        if (el.hasAttribute("value"))
            el.value = el.getAttribute("value");

    let newIndex = Array.from(selMac.options).findIndex(i => i.text == macInput.value);
    if (newIndex != -1) {
        selMac.selectedIndex = newIndex;
        macInput.style.display = "none";
    }
    selMac.onchange = e => {
        if (selMac.selectedIndex != selMac.options.length - 1) {
            macInput.value = selMac.options[selMac.selectedIndex].text;
            macInput.style.display = "none";
        } else {
            macInput.style.display = "table-cell";
        }
    }
}