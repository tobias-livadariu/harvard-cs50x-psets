// Note that ChatGPT helped me figure out the syntax for this function
function updatePerSecondSmoothly() {
    /* The idea in this function is to update the visual skeleton count that the user sees
    in intervals less than a second, so there is a more continuous visual gain in skeleton count,
    while still only updating the user's server-side skeleton count once per second to minimize
    strain on the server. */
    const interval = 50; // Update every 50ms (0.05 seconds)
    let gainPerInterval;

    // Fetch the initial per-second gain from the server
    fetch("/getPerSecondGain", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        gainPerInterval = data.skeletonsPerSecond / (1000 / interval);

        // Continuously update the skeleton count smoothly
        setInterval(() => {
            let skeletonCountElement = document.getElementById("skeleton-count");
            let currentSkeletonCount = parseFloat(skeletonCountElement.textContent);
            currentSkeletonCount += gainPerInterval;
            skeletonCountElement.textContent = Math.floor(currentSkeletonCount); // Optionally, round down to the nearest integer
        }, interval); // Update every 100ms
    })
    .catch(error => console.error("Error fetching per-second gain:", error));
}

// Start the smooth per-second updates
updatePerSecondSmoothly();
