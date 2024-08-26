// The point of this script is to check when the user's totalSkeletons count reaches certain thresholds where new elements should be added to the page
// When these thresholds are reached, the script will refresh the page to allow the new elements to generate

// Initialize a variable to track the previous skeleton count
let previousTotalSkeletons = parseInt(document.getElementById("total-skeletons").textContent);

function checkPageRefresh() {
    // Get the current total skeleton count from the page
    let currentTotalSkeletons = parseInt(document.getElementById("total-skeletons").textContent);

    // Check if currentTotalSkeletons and previousTotalSkeletons are valid numbers
    if (isNaN(currentTotalSkeletons) || isNaN(previousTotalSkeletons)) {
        console.log("Invalid skeleton count");
        return;
    }

    // Refresh the page if the total skeletons go from below 10 to above 10
    if (previousTotalSkeletons < 10 && currentTotalSkeletons >= 10) {
            location.reload();
        }

    // Update the previous total skeleton count for the next check
    previousTotalSkeletons = currentTotalSkeletons;
}

// Set an interval to repeadly check the skeleton count every 25 milliseconds
setInterval(checkPageRefresh, 25)
