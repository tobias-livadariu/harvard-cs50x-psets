// Note that ChatGPT helped me figure out the syntax for some parts of this function
function perSecondOperations() {
    /* The idea in this function is to update the visual skeleton count that the user sees
    in intervals less than a second, so there is a more continuous visual gain in skeleton count,
    while still only updating the user's server-side skeleton count once per second to minimize
    strain on the server. */
    const interval = 50; // Update every 50ms (0.05 seconds)
    let skeletonGainPerInterval; // Pre-initializing the skeletonGainPerInterval variable
    let accumulatedSkeletonGain = 0; // To accumulate fractional gains in skeleton count

    // Defining a function to fetch the per-second gain from the server.
    function fetchPerSecondGain() {
        fetch("/perSecondOperations", {
            method: "POST",
        })
        .then(response => response.json())
        .then(data => {
            skeletonGainPerInterval = data.skeletonsPerSecond / (1000 / interval);
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
        let currentSkeletonCount = parseInt(skeletonCountElement.textContent);
        let totalSkeletonCount = parseInt(totalSkeletonsElement.textContent);

        // Accumulate the gain
        accumulatedSkeletonGain += skeletonGainPerInterval;

        // Only update the display when at least 1 full skeleton is gained
        if (accumulatedSkeletonGain >= 1) {
            // Calculate the integer part of accumulatedSkeletonGain
            let increment = Math.floor(accumulatedSkeletonGain);
            currentSkeletonCount += increment;
            totalSkeletonCount += increment;
            accumulatedSkeletonGain -= increment; // Subtract the integer part, keeping the remainder

            // Display the updated values to the user
            skeletonCountElement.textContent = Math.floor(currentSkeletonCount)
            totalSkeletonsElement.textContent = Math.floor(totalSkeletonCount)
        }
    }, interval); // Update every 50ms

    // Re-fetch the per-second gain every second to account for changes
    setInterval(fetchPerSecondGain, 1000)
}

// Start the smooth per-second updates
perSecondOperations();
