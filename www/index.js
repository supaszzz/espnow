onload = () => {
    const selMac = document.getElementById("selMac");
    const macInput = document.getElementById("mac");
    let newIndex = Array.from(selMac.options).findIndex(i => i.text == macInput.value);
    if (newIndex != -1) {
        selMac.selectedIndex = newIndex;
        macInput.disabled = true;
    }
    selMac.onchange = e => {
        if (selMac.selectedIndex != selMac.options.length - 1) {
            macInput.value = selMac.options[selMac.selectedIndex].text;
            macInput.disabled = true;
        } else {
            macInput.disabled = false;
        }
    }
}