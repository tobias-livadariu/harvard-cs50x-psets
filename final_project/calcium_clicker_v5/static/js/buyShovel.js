function buyShovel() {
    // Fetching the /buyShovel route
    fetch("/buyShovel", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        // Checking if the transaction was successful
        if (data.wasSuccessful == false) {
            return;
        }

        let shovelButton = document.getElementById("shovel-button");
        let curShovel = data.curShovel;
        let maxShovel = data.maxShovel;
        let shovels = data.shovels;
        let shovelCost = data.shovelCost;
        let skeletonCount = data.skeletonCount;

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
            shovelButton.setAttribute("disabled", "true");
        }
        document.getElementById("skeleton-count").textContent = skeletonCount;
    });

    // Fetching the /updateStats route and updating the user's stats
    fetch("/updateStats", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById("skeletons-per-click").textContent = data.skeletonsPerClick
        document.getElementById("skeletons-per-second").textContent = data.skeletonsPerSecond
    });
}
