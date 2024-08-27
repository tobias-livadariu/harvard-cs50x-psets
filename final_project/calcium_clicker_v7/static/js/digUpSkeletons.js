// Using a variable to only let this function run if it is not already running
let isUpdating = 

function digUpSkeletons() {
    fetch("digUpSkeletons", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById("skeleton-count").textContent = formatNumberSuffix(data.skeletonCount);
        document.getElementById("total-skeletons").textContent = formatNumberSuffix(data.totalSkeletons);

        // Updating the key-value pairs in userSkeletons
        userSkeletons.skeletonCount = data.skeletonCount;
        userSkeletons.totalSkeletons = data.totalSkeletons;
    });
}
