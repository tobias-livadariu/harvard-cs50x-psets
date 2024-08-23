// Note that ChatGPT helped me figure out the syntax for this function
function updatePerSecondSmoothly() {
    const interval = 100; // Update every 100ms (0.1 seconds)
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
