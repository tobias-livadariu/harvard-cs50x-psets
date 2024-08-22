function buyShovel() {
    // Fetching the /buyAutodigger route
    fetch("/buyAutodigger", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById("num-autodiggers").textContent = data.numAutodiggers
        document.getElementById("autodigger-cost").textContent = data.autodiggerCost
    });

    // Fetching the /updateStats route and updating the user's stats
    fetch("/updateStats", {
        method: "POST"
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById("skeletons-per-click").textContent = data.skeletonsPerClick
        document.getElementById("skeletons-per-second").textContent = data.skeletonsPerSecond
    });
}
