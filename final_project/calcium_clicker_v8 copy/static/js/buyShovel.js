// Note that ChatGPT helped me develop this function

/* Using a variable to limit the user's ability to
buy a shovel until the most recent shovel transaction
has concluded. */
let canBuyShovel = true;

function buyShovel() {
    // Cancelling out of the function if canBuyShovel is false
    if (!canBuyShovel) {
        // Throw an error if canBuyShovel is false to prevent the function from running further
        throw new Error("Cannot buy shovel at the moment.")
    };
    canBuyShovel = false;

    // Fetching the /buyShovel route
    fetch("/buyShovel", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        // Checking if the transaction was successful
        if (!data.wasSuccessful) {
            throw new Error("Transaction failed."); // Throwing an error to skip the coming fetch call
        }

        let shovelButton = document.getElementById("shovel-button");
        let shovelDescription = document.getElementById("shovel-description");
        let curShovel = data.curShovel;
        let maxShovel = data.maxShovel;
        let shovels = data.shovels;
        let shovelCost = data.shovelCost;
        let skeletonCount = data.skeletonCount;

        if (curShovel < maxShovel) {
            shovelButton.textContent = `Forge a ${shovels[curShovel + 1]} Shovel (cost: ${formatNumberSuffix(shovelCost)} skeletons)`;
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
        shovelDescription.textContent = `Current shovel: ${shovels[curShovel]} (${formatNumberSuffix(shovelSkeletonsPerClick(curShovel))} skeletons per dig)`

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
            document.getElementById("skeletons-per-click").textContent = formatNumberSuffix(data.skeletonsPerClick)
            document.getElementById("skeletons-per-second").textContent = formatNumberSuffix(data.skeletonsPerSecond)
        }
    })
    // Allow the next request to process after this one
    .finally(() => {
        canBuyShovel = true;
    })
    // Handling errors
    .catch(error => {
        console.log("Error during purchase:", error)
        canBuyShovel = true; // Reset the flag even if there is an error
    })
}
