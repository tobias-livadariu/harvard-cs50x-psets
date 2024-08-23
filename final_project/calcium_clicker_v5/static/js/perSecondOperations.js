// Note that ChatGPT helped me figure out the syntax for this function
function perSecondOperations() {
    /* The idea in this function is to update the visual skeleton count that the user sees
    in intervals less than a second, so there is a more continuous visual gain in skeleton count,
    while still only updating the user's server-side skeleton count once per second to minimize
    strain on the server. */
    const interval = 50; // Update every 50ms (0.05 seconds)
    let gainPerInterval; // Pre-initializing the gainPerInterval variable

    // Defining a function to fetch the per-second gain from the server.
    function fetchPerSecondGain() {
        fetch("/perSecondOperations", {
            method: "POST",
        })
        .then(response => response.json())
        .then(data => {
            gainPerInterval = data.skeletonsPerSecond / (1000 / interval);
        })
        // Catching any error in the process of fetching initial per-second gain from the server
        .catch(error => console.error("Error fetching per-second gain:", error));
    }

    // Initial fetch
    fetchPerSecondGain();

    // Continuously update the skeleton count smoothly
    setInterval(() => {
        let skeletonCountElement = document.getElementById("skeleton-count");
        let totalSkeletonsElement = document.getElementById("total-skeletons");
        let currentSkeletonCount = parseFloat(skeletonCount.textContent);
        currentSkeletonCount += gainPerInterval;
        // Rounding the textContent in the "skeleton-count" element down to ensure
        // that it remains a float.
        skeletonCount.textContent = Math.floor(currentSkeletonCount);
    }, interval); // Update every 50ms
}

// Start the smooth per-second updates
updatePerSecond();
