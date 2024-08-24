/* Using a variable to limit the user's ability to
buy an autodigger until the most recent autodigger transaction
has concluded. */
let canBuyAutodigger = true;

function buyAutodigger() {
    // Cancelling out of the function if canBuyAutodigger is false
    if (!canBuyAutodigger) return;
    canBuyAutodigger = false;

    // Fetching the /buyAutodigger route
    fetch("/buyAutodigger", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        // Checking if the transaction was succesful
        if (data.wasSuccessful == false) {
            return;
        }

        document.getElementById("num-autodiggers").textContent = data.numAutodiggers;
        document.getElementById("autodigger-cost").textContent = data.autodiggerCost;
        document.getElementById("skeleton-count").textContent = data.skeletonCount;

        // Allow the next request to process after this one
        canBuyAutodigger = true;
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
