/* Using a variable to limit the user's ability to
buy ten autodiggers until the full transaction
has concluded. */
let canBuyTenAutodiggers = true;

function buyTenAutodiggers() {
    if (!canBuyTenAutodiggers) {
        // Throw an error if canBuyTenAutodiggers is false to prevent the function from running further
        throw new Error("Cannot buy ten autodiggers at the moment.");
    }
    canBuyTenAutodiggers = false;

    fetch("numAutodiggersBuyable", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        /* Getting the max number of autodiggers the user can buy. */
        let numAutodiggersBuyable = data.numAutodiggersBuyable;
        if (numAutodiggersBuyable < 10) {
            throw new Error("10x transaction failed.");
        }
        let costForTen = data.costForTen;
        let numAutodiggers = data.numAutodiggers;
        let skeletonCount = data.skeletonCount;

        /* Buying 10 autodiggers for the user. */
        return fetch (`/buyAutodigger?numBuying=10&numAutodiggers=${numAutodiggers}&cost=${costForTen}&skeletonCount=${skeletonCount}`, {
            method: "POST",
        });
    })
    .then(response => {
        if (response) {
            return response.json();
        }
    })
    .then(data => {
        if (data) {
            document.getElementById("num-autodiggers").textContent = data.numAutodiggers;
            document.getElementById("autodigger-cost").textContent = formatNumberSuffix(data.autodiggerCost);

            // Updating the key-value pairs in userSkeletons
            userSkeletons.skeletonCount = data.skeletonCount;

            return fetch("/updateStats", {
                method: "POST",
            });
        }
    })
    .then(response => {
        if (response) {
            return response.json();
        }
    })
    .then(data => {
        if (data) {
            document.getElementById("skeletons-per-click").textContent = formatNumberSuffix(data.skeletonsPerClick);
            document.getElementById("skeletons-per-second").textContent = formatNumberSuffix(data.skeletonsPerSecond);
        }
    })
    // Allow the next request to process after this one
    .finally(() => {
        canBuyTenAutodiggers = true;
    })
    // Handling errors
    .catch(error => {
        console.error("Error during purchase:", error);
        canBuyTenAutodiggers = true; // Reset the flag even if there is an error
    });
}
