// The point of this script is to check when the user's totalSkeletons count reaches certain thresholds where new elements should be added to the page
// When these thresholds are reached, the script will refresh the page to allow the new elements to generate

// Initialize a variable to track the previous skeleton count
let previousTotalSkeletons = parseInt(document.getElementById("total-skeletons").textContent);
let refreshInterval; // Declare this in the outer scope so it's accessible for clearing

function checkPageRefresh() {
    // Get the current total skeleton count from the page
    let currentTotalSkeletons = parseInt(document.getElementById("total-skeletons").textContent);

    // Check if currentTotalSkeletons and previousTotalSkeletons are valid numbers
    if (isNaN(currentTotalSkeletons) || isNaN(previousTotalSkeletons)) {
        console.log("Invalid skeleton count");
        return;
    }

    // Refresh the page if the total skeletons go from below 10 to 10 or above
    if (previousTotalSkeletons < 10 && currentTotalSkeletons >= 10) {
        location.reload();
    }

    // Stop refreshing if both currentTotalSkeletons and previousTotalSkeletons are above 10
    if (previousTotalSkeletons >= 10 && currentTotalSkeletons >= 10) {  // VERY IMPORTANT NOTE::: if I ever add more elements beyond the current final block, I will need to adjust this amount
        clearInterval(refreshInterval);
    }

    // Update the previous total skeleton count for the next check
    previousTotalSkeletons = currentTotalSkeletons;
}

// Set an interval to repeatedly check the skeleton count every 25 milliseconds if previousTotalSkeletons is below the maximum threshold valid
// VERY IMPORTANT NOTE::: if I ever add more elements beyond the current final block, I will need to adjust this amount
document.addEventListener("DOMContentLoaded", function() {
    if (previousTotalSkeletons < 10) {
        refreshInterval = setInterval(checkPageRefresh, 25);
    }
})
