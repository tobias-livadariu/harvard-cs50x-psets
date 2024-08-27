// Using a variable to only let this function run if it is not already running
let canDigUpSkeletons = true;

function digUpSkeletons() {
    // Checking if currently digging skeletons
    if (!canDigUpSkeletons) {
        // Throw an error if canDigUpSkeletons is false to prevent the function from running further
        throw new Error("Cannot dig more skeletons at the moment.");
    }
    canDigUpSkeletons = false;

    fetch("digUpSkeletons", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById("skeleton-count").textContent = formatNumberSuffix(data.skeletonCount);
        document.getElementById("total-skeletons").textContent = formatNumberSuffix(data.totalSkeletons);

        // Updating the key-value pairs in userSkeletons
        userSkeletons.skeletonCount = data.skeletonCount;
        userSkeletons.totalSkeletons = data.totalSkeletons;
    })
    .finally(() => {
        canDigUpSkeletons = true
    })
    // Handling errors
    .catch(error => {
        console.error("Error during dig:", error);
        canDigUpSkeletons = true; // Reset the flag even if there is an error
    });
}
