# # Jakub Jaśków 268416
include("utils/hilb.jl")
include("utils/matcond.jl")

using LinearAlgebra

function solveLinear(A, n, k)
    x = ones(Float64, n)
    b = A * x

    xGauss = A\b
    xInv = inv(A)*b

    errGaus = norm(x - xGauss)/norm(x)
    errInv = norm(x - xInv)/norm(x)
    if k < 0
        println(rpad(n, 3), 
        " & ", rpad(cond(A), 25), 
        " & ", rpad(rank(A), 10), 
        " & ", rpad(errGaus, 25), 
        " & ", rpad(errInv, 25), 
        " \\\\\\hline")
    else
        println(rpad(n, 3), 
        " & ", rpad(cond(A), 25), 
        " & ", rpad(rank(A), 10), 
        " & ", rpad(errGaus, 25), 
        " & ", rpad(errInv, 25), 
        " & ", rpad("10^$k", 6), 
        " \\\\\\hline")
    end
end

dist1 = 3
dist2 = 25
dist3 = 10
println("\nZadanie 3")
println("########### Hilbert's Matrix ###########")
println(rpad("n", dist1), 
" & ", rpad("cond(A)", dist2), 
" & ", rpad("rank(A)", dist3), 
" & ", rpad("Gauss Relative Error", dist2), 
" & ", rpad("Invert Relative Error", dist2))
for i in 1:4:64
    solveLinear(hilb(i), i, -1)
end

println("########### Random Matrix ###########")
println(rpad("n", dist1), 
" & ", rpad("cond(A)", dist2), 
" & ", rpad("rank(A)", dist3), 
" & ", rpad("Gauss Relative Error", dist2), 
" & ", rpad("Invert Relative Error", dist2), 
" & ", rpad("c", 3))
for i in [5, 10, 20]
    for k in [0, 1, 3 , 7, 12, 16]
        solveLinear(matcond(i, Float64(10^k)), i, k)
    end
end
