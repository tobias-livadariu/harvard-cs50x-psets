/* Note that ChatGPT helped teach me how to implement the use of localStorage
into this function. */

// Assigning the value in localStorage of 'previousTotalSkeletons' to a variable
let previousTotalSkeletons = parseInt(localStorage.getItem('previousTotalSkeletons'));

// Checking if there is a number in localStorage for 'previousTotalSkeletons'
if (isNaN(previousTotalSkeletons)) {
    // If there is not a number, set previousTotalSkeletons to the current number of skeletons owned by the user
    previousTotalSkeletons = userSkeletons.totalSkeletons;
    localStorage.setItem('previousTotalSkeletons', previousTotalSkeletons);
}

// Defining a function to check if the page should be reset if new elements should be introduced to the user
function checkPageRefresh() {
    // Get the current total skeleton count
    let currentTotalSkeletons = userSkeletons.totalSkeletons;

    // Verifying that currentTotalSkeletons and previousTotalSkeletons are valid numbers before proceeding
    if (isNaN(currentTotalSkeletons) || isNaN(previousTotalSkeletons)) {
        console.log("Invalid skeleton count");
        return;
    }

    // Refresh the page and reassign the value in local storage for previousTotalSkeletons if the total skeletons go from below 10 to 10 or more
    if (previousTotalSkeletons < 10 && currentTotalSkeletons >= 10) {
        localStorage.setItem('previousTotalSkeletons', currentTotalSkeletons);
        location.reload();
    } else {
        // Update and store the previous total skeleton count for the next check
        previousTotalSkeletons = currentTotalSkeletons;
        localStorage.setItem('previousTotalSkeletons', previousTotalSkeletons);

        // If both previousTotalSkeletons and currentTotalSkeletons exceed a certain threshold, stop the interval because it is no longer necessary
        if (previousTotalSkeletons >= 10 && currentTotalSkeletons >= 10) {
            clearInterval(checkInterval); // Stop checking TODO:: change this threshold in the future if you make more element chunks to introduce to the user
        }
    }
}

// Set an interval to repeatedly check the skeleton count every 25 milliseconds if previousTotalSkeletons is below 10
let checkInterval;
if (previousTotalSkeletons < 10) {
    checkInterval = setInterval(checkPageRefresh, 25);
}
