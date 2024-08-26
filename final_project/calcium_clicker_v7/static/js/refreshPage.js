// Initialize a variable to track the previous skeleton count
let previousTotalSkeletons = userSkeletons.totalSkeletons;

function checkPageRefresh() {
    // Get the current total skeleton count
    let currentTotalSkeletons = userSkeletons.totalSkeletons;

    // Check if currentTotalSkeletons and previousTotalSkeletons are valid numbers
    if (isNaN(currentTotalSkeletons) || isNaN(previousTotalSkeletons)) {
        console.log("Invalid skeleton count");
        return;
    }

    // Refresh the page if the total skeletons go from below 10 to 10
    if (previousTotalSkeletons < 10 && currentTotalSkeletons >= 10) {
        console.log(`previousTotalSkeletons: ${previousTotalSkeletons}`);
        console.log(`currentTotalSkeletons: ${currentTotalSkeletons}`);
        location.reload();
    }

    // Stop the interval if both are above 10
    if (previousTotalSkeletons >= 10 && currentTotalSkeletons >= 10) {
        console.log("Both values are above 10, stopping the interval.");
        clearInterval(refreshInterval);
    }

    // Update the previous total skeleton count for the next check
    previousTotalSkeletons = currentTotalSkeletons;
}

// Only set the interval if the initial skeleton count is below 10
if (previousTotalSkeletons < 10) {
    var refreshInterval = setInterval(checkPageRefresh, 25);
}
