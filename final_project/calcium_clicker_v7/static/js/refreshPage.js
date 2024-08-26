/* Note that ChatGPT helped teach me how to implement the use of localStorage
into this function. */

// Initialize a variable to track the previous skeleton count
let previousTotalSkeletons = parseInt(localStorage.getItem('previousTotalSkeletons'));

if (isNaN(previousTotalSkeletons)) {
    // If there is nothing in localStorage, set previousTotalSkeletons to the current value
    previousTotalSkeletons = userSkeletons.totalSkeletons;
    localStorage.setItem('previousTotalSkeletons', previousTotalSkeletons);
}

function checkPageRefresh() {
    // Get the current total skeleton count
    let currentTotalSkeletons = userSkeletons.totalSkeletons;

    // Check if currentTotalSkeletons and previousTotalSkeletons are valid numbers before proceeding
    if (isNaN(currentTotalSkeletons) || isNaN(previousTotalSkeletons)) {
        console.log("Invalid skeleton count");
        return;
    }

    // Refresh the page if the total skeletons go from below 10 to 10 or more
    if (previousTotalSkeletons < 10 && currentTotalSkeletons >= 10) {
        console.log(`previousTotalSkeletons: ${previousTotalSkeletons}`);
        console.log(`currentTotalSkeletons: ${currentTotalSkeletons}`);
        localStorage.setItem('previousTotalSkeletons', currentTotalSkeletons); // Store the current value
        location.reload();
    } else {
        // Update the previous total skeleton count for the next check
        previousTotalSkeletons = currentTotalSkeletons;
        localStorage.setItem('previousTotalSkeletons', previousTotalSkeletons); // Store the updated value

        // If both values are 10 or more, stop the interval
        if (previousTotalSkeletons >= 10 && currentTotalSkeletons >= 10) {
            clearInterval(checkInterval); // Stop checking
        }
    }
}

// Set an interval to repeatedly check the skeleton count every 25 milliseconds if previousTotalSkeletons is below 10
let checkInterval;
if (previousTotalSkeletons < 10) {
    checkInterval = setInterval(checkPageRefresh, 25);
}
