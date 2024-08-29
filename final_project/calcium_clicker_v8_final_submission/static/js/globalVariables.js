/* Defining a variable that can be used
to keep track of the user's current and
total skeleton counts. */
let userSkeletons = {
    skeletonCount: 0,
    totalSkeletons: 0
}

document.addEventListener("DOMContentLoaded", function() {
    userSkeletons.skeletonCount = document.getElementById("skeleton-count").textContent
    userSkeletons.totalSkeletons = document.getElementById("total-skeletons").textContent
})
