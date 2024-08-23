// Note that ChatGPT helped me figure out the syntax for this function
function updatePerSecond() {
    /* The idea in this function is to update the visual skeleton count that the user sees
    in intervals less than a second, so there is a more continuous visual gain in skeleton count,
    while still only updating the user's server-side skeleton count once per second to minimize
    strain on the server. */
    const interval = 50; // Update every 50ms (0.05 seconds)
    let gainPerInterval; // Pre-initializing the gainPerInterval variable

    // Fetching the initial per-second gain from the server
    fetch("/updatePerSecond", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        gainPerInterval = data.skeletonsPerSecond / (1000 / interval);

        // Continuously update the skeleton count smoothly
        setInterval(() => {
            let skeletonCount = document.getElementById("skeleton-count");
            let currentSkeletonCount = parseFloat(skeletonCount.textContent);
            currentSkeletonCount += gainPerInterval;
            // Rounding the textContent in the "skeleton-count" element down to ensure
            // that it remains a float.
            skeletonCount.textContent = Math.floor(currentSkeletonCount);
        }, interval); // Update every 50ms
    })
    // Catching any error in the process of fetching initial per-second gain from the server
    .catch(error => console.error("Error fetching per-second gain:", error));
}

// Start the smooth per-second updates
updatePerSecond();
