using CSV
using DataFrames
using Plots

# read in csv
file = CSV.File("accelero.txt")
data = DataFrame(file)

# plot
plot(data.time, data.x, labels="x")
plot!(data.time, data.y, labels="y")
plot!(data.time, data.z, labels="z")
title!("Acceleration vs Time")
xlabel!("Time (s)")
ylabel!("Acceleration (g)")

# integrate to get velocities
v_x = zeros(length(data.x))
v_y = zeros(length(data.y))
v_z = zeros(length(data.z))
mac_x = 0.0
mac_y = 0.0
mac_z = 0.0
for i ∈ 1:length(data.time)
    mac_x += (data.time[i] - data.time[i - 1]) * data.x[i]
    mac_y += (data.time[i] - data.time[i - 1]) * data.y[i]
    mac_z += (data.time[i] - data.time[i - 1]) * data.z[i]
    v_x[i] = mac_x
    v_y[i] = mac_y
    v_z[i] = mac_z
end
