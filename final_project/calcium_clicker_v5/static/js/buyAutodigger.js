function buyAutodigger() {
    // Fetching the /buyAutodigger route
    fetch("/buyAutodigger", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        // Checking if the transaction was succesful
        if data.wasSuccessful == False {
            return;
        }

        document.getElementById("num-autodiggers").textContent = data.numAutodiggers;
        document.getElementById("autodigger-cost").textContent = data.autodiggerCost;
        document.getElementById("skeleton-count").textContent = data.skeletonCount;
    });

    // Fetching the /updateStats route and updating the user's stats
    fetch("/updateStats", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById("skeletons-per-click").textContent = data.skeletonsPerClick;
        document.getElementById("skeletons-per-second").textContent = data.skeletonsPerSecond;
    });
}
