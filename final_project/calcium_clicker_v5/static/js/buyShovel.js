function buyShovel() {
    // Fetching the /buyShovel route
    fetch("/buyShovel", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        let shovelButton = document.getElementById("shovel-button");
        let curShovel = data.curShovel;
        let maxShovel = data.maxShovel;
        let shovels = data.shovels;
        let shovelCost = data.shovelCost;

        if (curShovel < maxShovel) {
            shovelButton.textContent = `Forge a ${shovels[curShovel + 1]} shovel (cost: ${shovelCost} skeletons)`;
            // Remove dark class and enable the button (this is not necessary, but I am writing it for clarity)
            shovelButton.classList.remove('btn-dark');
            shovelButton.removeAttribute('disabled');
        } else {
            // Change the text content in the button to indicate that it is maxed
            shovelButton.textContent = "Your shovel is max level!";
            // Add the dark class to the button and disable it
            shovelButton.classList.add("btn-dark");
            shovelButton.setAttribute("disabled", "true")
        }
    });

    // Fetching the /updateStats route
    fetch("/updateStats", {
        method: "POST"
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById("")
    });
}
