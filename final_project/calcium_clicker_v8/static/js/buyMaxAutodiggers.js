/* Using a variable to limit the user's ability to
buy max autodiggers until the full transaction
has concluded. */
let canBuyMaxAutodiggers = true;

function buyMaxAutodiggers() {
    if (!canBuyMaxAutodiggers) {
        // Throw an error if canBuyMaxAutodiggers is false to prevent the function from running further
        throw new Error("Cannot buy max autodiggers at the moment.");
    }
    canBuyMaxAutodiggers = false;

    fetch("numAutodiggersBuyable", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        /* Getting the max number of autodiggers the user can buy. */
        let numAutodiggersBuyable = data.numAutodiggersBuyable;
        if (numAutodiggersBuyable == 0) {
            throw new Error("Buy max transaction failed.");
        }
        let costForMax = data.costForMax;
        let numAutodiggers = data.numAutodiggers;
        let skeletonCount = data.skeletonCount;

        /* Buying max autodiggers for the user. */
        return fetch (`/buyAutodigger?numBuying=${numAutodiggersBuyable}&numAutodiggers=${numAutodiggers}&cost=${costForMax}&skeletonCount=${skeletonCount}`, {
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
        canBuyMaxAutodiggers = true;
    })
    // Handling errors
    .catch(error => {
        console.error("Error during purchase:", error);
        canBuyMaxAutodiggers = true; // Reset the flag even if there is an error
    });
}
