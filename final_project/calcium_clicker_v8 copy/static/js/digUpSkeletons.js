// Using a variable to only let this function run under certain conditions
let numQueued = 0;

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
