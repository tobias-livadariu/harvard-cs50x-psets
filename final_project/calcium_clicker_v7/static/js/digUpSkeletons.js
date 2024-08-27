// Using a variable to only let this function run under certain conditions
let numQueued = 0;
// Using a second variable to limit how quickly the DOM can update if the user is spam clicking
// Note that ChatGPT taught me how to use the methods of the data object
let lastUpdate = Date.now()

function digUpSkeletons() {
    // Checking if numQueued is too large
    if (numQueued > 10) {
        // Throw an error if canDigUpSkeletons is false to prevent the function from running further
        throw new Error("Cannot dig more skeletons at the moment.");
    }
    numQueued++;

    fetch("digUpSkeletons", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        // Updating the key-value pairs in userSkeletons
        userSkeletons.skeletonCount = data.skeletonCount;
        userSkeletons.totalSkeletons = data.totalSkeletons;

        // Only update the DOM if a certain amount of time has passed since the last update
        const now = Date.now()
        if (now - lastUpdate > 100) {
            document.getElementById("skeleton-count").textContent = formatNumberSuffix(data.skeletonCount);
            document.getElementById("total-skeletons").textContent = formatNumberSuffix(data.totalSkeletons);
            lastUpdate = now;
        }
    })
    .finally(() => {
        numQueued--;
    })
    // Handling errors
    .catch(error => {
        console.error("Error during dig:", error);
        numQueued--; // Decrement the flag even if there is an error
    });
}
