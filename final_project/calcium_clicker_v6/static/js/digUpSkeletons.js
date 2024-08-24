function digUpSkeletons() {
    fetch("digUpSkeletons", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById("skeleton-count").textContent = data.skeletonCount;
        document.getElementById("total-skeletons").textContent = data.totalSkeletons;

        // Updating the key-value pairs in userSkeletons
        userSkeletons.skeletonCount = data.skeletonCount;
        userSkeletons.totalSkeletons = data.totalSkeletons;
    });
}
