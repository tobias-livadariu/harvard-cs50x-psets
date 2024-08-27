// Note that ChatGPT helped me develop this function

/* Using a variable to limit the user's ability to
buy an autodigger until the most recent autodigger transaction
has concluded. */
let canBuyAutodigger = true;

function buyAutodigger() {
    // Cancelling out of the function if canBuyAutodigger is false
    if (!canBuyAutodigger) {
        // Throw an error if canBuyAutodigger is false to prevent the function from running further
        throw new Error("Cannot buy autodigger at the moment.")
    };
    canBuyAutodigger = false;

    // Fetching the /buyAutodigger route
    fetch("/buyAutodigger", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        // Checking if the transaction was succesful
        if (data.wasSuccessful == false) {
            throw new Error("Transaction failed."); // Throwing an error to skip the coming fetch call
        }

        document.getElementById("num-autodiggers").textContent = data.numAutodiggers;
        document.getElementById("autodigger-cost").textContent = formatNumberSuffix(data.autodiggerCost);

        // Updating the key-value pairs in userSkeletons
        userSkeletons.skeletonCount = data.skeletonCount;

        // Fetching the /updateStats route and updating the user's stats
        return fetch("/updateStats", {
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
            document.getElementById("skeletons-per-click").textContent = formatNumberSuffix(data.skeletonsPerClick);
            document.getElementById("skeletons-per-second").textContent = formatNumberSuffix(data.skeletonsPerSecond);
        }
    })
    // Allow the next request to process after this one
    .finally(() => {
        canBuyAutodigger = true;
    })
    // Handling errors
    .catch(error => {
        console.error("Error during purchase:", error);
        canBuyAutodigger = true; // Reset the flag even if there is an error
    });
}
