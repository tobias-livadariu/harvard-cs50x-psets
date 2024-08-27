// Defining two functions that refresh the values in the skeletonCount and totalSkeletons text boxes.
// Note that this has to be done here rather than in the functions that actually change the values,
// because too many functions are touching skeletonCount and totalSkeletons.

skeletonCount = 0
totalSkeletons = 0

function loadValues() {
    skeletonCount = 
}

function resyncDOM() {
    document.getElementById("skeleton-count").textContent = formatNumberSuffix(userSkeletons.skeletonCount)
    document.getElementById("total-skeletons").textContent = formatNumberSuffix(userSkeletons.totalSkeletons)
}

document.getEventHandler("DOMContentLoaded", function() {
    setInterval(resyncDOM, 25)
})
