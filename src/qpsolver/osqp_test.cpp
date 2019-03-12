#include "gtest/gtest.h"
#include "osqp_solver.hpp"

using namespace osqp_solver;

TEST(OSQPTestCase, TestSimpleQP) {
    using SimpleQP = QP<2, 3, double>;
    OSQPSolver<SimpleQP> prob;
    Eigen::Vector2d sol, expect;

    SimpleQP qp;
    qp.P << 4, 1,
            1, 2;
    qp.q << 1, 1;
    qp.A << 1, 1,
            1, 0,
            0, 1;
    qp.l << 1, 0, 0;
    qp.u << 1, 0.7, 0.7;

    OSQPSolver<SimpleQP>::Settings settings;
    settings.rho = 1.0;
    settings.max_iter = 50;
    settings.eps_rel = 1e-4f; // set below isApprox() threshold
    settings.eps_abs = 1e-4f;

    prob.solve(qp, settings);
    sol = prob.x;

    expect << 0.3, 0.7;
    ASSERT_TRUE(sol.isApprox(expect, 1e-3f));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}