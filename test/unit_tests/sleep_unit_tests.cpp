// System Libraries
#include <chrono>
#include <fstream>
#include <memory>
#include <stdio.h>
#include <thread>
#include <vector>

// Unit Test Headers
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

// Directory Config Headers
#include "DirectoryConfig.hpp"

// Sleep Headers
#include "sleep.hpp"

const static std::string RESULTS_DIR = "/test/results/";

std::vector<std::tuple<uint64_t, uint64_t, int64_t>> test_sleep_ms(uint32_t duration_ms, uint32_t sample_count) {
	std::vector<std::tuple<uint64_t, uint64_t, int64_t>> start_end_times{};
	for (int i = 0; i < sample_count; i++) {
		uint64_t start_ns, end_ns;
		start_ns = sleep::now_ns();
		sleep::sleep_ms(duration_ms);
		end_ns = sleep::now_ns();
		start_end_times.push_back(std::make_tuple(start_ns, end_ns, end_ns - start_ns - (duration_ms * 1'000'000)));
	}
	return start_end_times;
}

std::vector<std::tuple<uint64_t, uint64_t, int64_t>> test_sleep_ms_corrected(uint32_t duration_ms, uint32_t sample_count) {
	std::vector<std::tuple<uint64_t, uint64_t, int64_t>> start_end_times{};
	int64_t error_us = 0;
	for (int i = 0; i < sample_count; i++) {
		uint64_t start_ns, end_ns;
		uint64_t start_us;
		start_ns = sleep::now_ns();
		start_us = sleep::now_us();
		sleep::sleep_ms_corrected(duration_ms, error_us);
		error_us += ((int64_t)sleep::now_us() - (int64_t)start_us) - (duration_ms * 1'000);
		end_ns = sleep::now_ns();
		start_end_times.push_back(std::make_tuple(start_ns, end_ns, error_us * 1'000));
	}
	return start_end_times;
}

std::vector<std::tuple<uint64_t, uint64_t, int64_t>> test_sleep_us(uint32_t duration_us, uint32_t sample_count) {
	std::vector<std::tuple<uint64_t, uint64_t, int64_t>> start_end_times{};
	for (int i = 0; i < sample_count; i++) {
		uint64_t start_ns, end_ns;
		start_ns = sleep::now_ns();
		sleep::sleep_us(duration_us);
		end_ns = sleep::now_ns();
		start_end_times.push_back(std::make_tuple(start_ns, end_ns, end_ns - start_ns - (duration_us * 1'000)));
	}
	return start_end_times;
}

void save_results(std::vector<std::tuple<uint64_t, uint64_t, int64_t>> start_end_times, std::string file_name) {
	std::ofstream output_file = std::ofstream(file_name, std::ios::out);
	std::string line = "Start,End,Error\n";
	output_file.write(line.c_str(), line.size());
	for (auto [start, end, error] : start_end_times) {
		std::string line = std::to_string(start) + "," + std::to_string(end) + "," + std::to_string(error) + "\n";
		output_file.write(line.c_str(), line.size());
	}
}

/*************************************************************************************************
* Main Method
*************************************************************************************************/
int main( int argc, char* argv[] ) {
  	int result = Catch::Session().run( argc, argv );
	return result;
}

/*************************************************************************************************/
/* sleep_ms Tests																				 */
/*************************************************************************************************/
TEST_CASE("Checking sleep_ms with sleep duration of 1 second.", "[sleep_ms][test][long]") {
	uint32_t ms = 1000;
	REQUIRE_NOTHROW(save_results(test_sleep_ms(ms, 10 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms with sleep duration of 500 milliseconds.", "[sleep_ms][test][long]") {
	uint32_t ms = 500;
	REQUIRE_NOTHROW(save_results(test_sleep_ms(ms, 10 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms with sleep duration of 250 milliseconds.", "[sleep_ms][test][long]") {
	uint32_t ms = 250;
	REQUIRE_NOTHROW(save_results(test_sleep_ms(ms, 10 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms with sleep duration of 50 milliseconds.", "[sleep_ms][test][short]") {
	uint32_t ms = 50;
	REQUIRE_NOTHROW(save_results(test_sleep_ms(ms, 5 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms with sleep duration of 10 milliseconds.", "[sleep_ms][test][short]") {
	uint32_t ms = 10;
	REQUIRE_NOTHROW(save_results(test_sleep_ms(ms, 1 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms with sleep duration of 5 milliseconds.", "[sleep_ms][test][short]") {
	uint32_t ms = 5;
	REQUIRE_NOTHROW(save_results(test_sleep_ms(ms, 1 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms with sleep duration of 4 milliseconds.", "[sleep_ms][test][short]") {
	uint32_t ms = 4;
	REQUIRE_NOTHROW(save_results(test_sleep_ms(ms, 1 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms with sleep duration of 3 milliseconds.", "[sleep_ms][test][short]") {
	uint32_t ms = 3;
	REQUIRE_NOTHROW(save_results(test_sleep_ms(ms, 1 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms with sleep duration of 2 milliseconds.", "[sleep_ms][test][short]") {
	uint32_t ms = 2;
	REQUIRE_NOTHROW(save_results(test_sleep_ms(ms, 1 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms with sleep duration of 1 milliseconds.", "[sleep_ms][test][short]") {
	uint32_t ms = 1;
	REQUIRE_NOTHROW(save_results(test_sleep_ms(ms, 1 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms-" + std::to_string(ms) + "ms.csv"));
}


/*************************************************************************************************/
/* sleep_ms Benchmarks																			 */
/*************************************************************************************************/
TEST_CASE("Benchmarking sleep_ms.", "[sleep_ms][benchmark]") {
	uint32_t ms = 1'000;
	BENCHMARK("1 second"){ return sleep::sleep_ms(ms); };
	ms = 500;
	BENCHMARK("500 milliseconds"){ return sleep::sleep_ms(ms); };
	ms = 250;
	BENCHMARK("250 milliseconds"){ return sleep::sleep_ms(ms); };
	ms = 50;
	BENCHMARK("50 milliseconds"){ return sleep::sleep_ms(ms); };
	ms = 10;
	BENCHMARK("10 milliseconds"){ return sleep::sleep_ms(ms); };
	ms = 5;
	BENCHMARK("5 milliseconds"){ return sleep::sleep_ms(ms); };
	ms = 4;
	BENCHMARK("4 milliseconds"){ return sleep::sleep_ms(ms); };
	ms = 3;
	BENCHMARK("3 milliseconds"){ return sleep::sleep_ms(ms); };
	ms = 2;
	BENCHMARK("2 milliseconds"){ return sleep::sleep_ms(ms); };
	ms = 1;
	BENCHMARK("1 milliseconds"){ return sleep::sleep_ms(ms); };
}


/*************************************************************************************************/
/* sleep_ms_corrected Tests																		 */
/*************************************************************************************************/
TEST_CASE("Checking sleep_ms_corrected with sleep duration of 1 second.", "[sleep_ms_corrected][test][long]") {
	uint32_t ms = 1000;
	REQUIRE_NOTHROW(save_results(test_sleep_ms_corrected(ms, 10 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms_corrected-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms_corrected with sleep duration of 500 milliseconds.", "[sleep_ms_corrected][test][long]") {
	uint32_t ms = 500;
	REQUIRE_NOTHROW(save_results(test_sleep_ms_corrected(ms, 10 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms_corrected-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms_corrected with sleep duration of 250 milliseconds.", "[sleep_ms_corrected][test][long]") {
	uint32_t ms = 250;
	REQUIRE_NOTHROW(save_results(test_sleep_ms_corrected(ms, 10 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms_corrected-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms_corrected with sleep duration of 50 milliseconds.", "[sleep_ms_corrected][test][short]") {
	uint32_t ms = 50;
	REQUIRE_NOTHROW(save_results(test_sleep_ms_corrected(ms, 5 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms_corrected-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms_corrected with sleep duration of 10 milliseconds.", "[sleep_ms_corrected][test][short]") {
	uint32_t ms = 10;
	REQUIRE_NOTHROW(save_results(test_sleep_ms_corrected(ms, 1 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms_corrected-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms_corrected with sleep duration of 5 milliseconds.", "[sleep_ms_corrected][test][short]") {
	uint32_t ms = 5;
	REQUIRE_NOTHROW(save_results(test_sleep_ms_corrected(ms, 1 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms_corrected-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms_corrected with sleep duration of 4 milliseconds.", "[sleep_ms_corrected][test][short]") {
	uint32_t ms = 4;
	REQUIRE_NOTHROW(save_results(test_sleep_ms_corrected(ms, 1 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms_corrected-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms_corrected with sleep duration of 3 milliseconds.", "[sleep_ms_corrected][test][short]") {
	uint32_t ms = 3;
	REQUIRE_NOTHROW(save_results(test_sleep_ms_corrected(ms, 1 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms_corrected-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms_corrected with sleep duration of 2 milliseconds.", "[sleep_ms_corrected][test][short]") {
	uint32_t ms = 2;
	REQUIRE_NOTHROW(save_results(test_sleep_ms_corrected(ms, 1 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms_corrected-" + std::to_string(ms) + "ms.csv"));
}

TEST_CASE("Checking sleep_ms_corrected with sleep duration of 1 milliseconds.", "[sleep_ms_corrected][test][short]") {
	uint32_t ms = 1;
	REQUIRE_NOTHROW(save_results(test_sleep_ms_corrected(ms, 1 * (1000 / ms)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_ms_corrected-" + std::to_string(ms) + "ms.csv"));
}


/*************************************************************************************************/
/* sleep_us Tests																				 */
/*************************************************************************************************/
TEST_CASE("Checking sleep_us with sleep duration of 10 milliseconds.", "[sleep_us][test][short]") {
	uint32_t us = 10'000;
	REQUIRE_NOTHROW(save_results(test_sleep_us(us, 1 * (1'000'000 / us)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_us-" + std::to_string(us) + "us.csv"));
}

TEST_CASE("Checking sleep_us with sleep duration of 1 millisecond.", "[sleep_us][test][short]") {
	uint32_t us = 1'000;
	REQUIRE_NOTHROW(save_results(test_sleep_us(us, 1 * (1'000'000 / us)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_us-" + std::to_string(us) + "us.csv"));
}

TEST_CASE("Checking sleep_us with sleep duration of 500 microseconds.", "[sleep_us][test][short]") {
	uint32_t us = 500;
	REQUIRE_NOTHROW(save_results(test_sleep_us(us, 0.5 * (1'000'000 / us)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_us-" + std::to_string(us) + "us.csv"));
}

TEST_CASE("Checking sleep_us with sleep duration of 250 microseconds.", "[sleep_us][test][short]") {
	uint32_t us = 250;
	REQUIRE_NOTHROW(save_results(test_sleep_us(us, 0.5 * (1'000'000 / us)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_us-" + std::to_string(us) + "us.csv"));
}

TEST_CASE("Checking sleep_us with sleep duration of 50 microseconds.", "[sleep_us][test][short]") {
	uint32_t us = 50;
	REQUIRE_NOTHROW(save_results(test_sleep_us(us, 0.25 * (1'000'000 / us)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_us-" + std::to_string(us) + "us.csv"));
}

TEST_CASE("Checking sleep_us with sleep duration of 10 microseconds.", "[sleep_us][test][short]") {
	uint32_t us = 10;
	REQUIRE_NOTHROW(save_results(test_sleep_us(us, 0.25 * (1'000'000 / us)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_us-" + std::to_string(us) + "us.csv"));
}

TEST_CASE("Checking sleep_us with sleep duration of 5 microseconds.", "[sleep_us][test][short]") {
	uint32_t us = 5;
	REQUIRE_NOTHROW(save_results(test_sleep_us(us, 0.25 * (1'000'000 / us)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_us-" + std::to_string(us) + "us.csv"));
}

TEST_CASE("Checking sleep_us with sleep duration of 1 microseconds.", "[sleep_us][test][short]") {
	uint32_t us = 1;
	REQUIRE_NOTHROW(save_results(test_sleep_us(us, 0.1 * (1'000'000 / us)), PROJECT_DIRECTORY + RESULTS_DIR + "sleep_us-" + std::to_string(us) + "us.csv"));
}


/*************************************************************************************************/
/* sleep_us Benchmarks																			 */
/*************************************************************************************************/
TEST_CASE("Benchmarking sleep_us.", "[sleep_us][benchmark]") {
	uint32_t us = 10'000;
	BENCHMARK("10 milliseconds"){ return sleep::sleep_us(us); };
	us = 1'000;
	BENCHMARK("1 millisecond"){ return sleep::sleep_us(us); };
	us = 500;
	BENCHMARK("500 microseconds"){ return sleep::sleep_us(us); };
	us = 250;
	BENCHMARK("250 microseconds"){ return sleep::sleep_us(us); };
	us = 50;
	BENCHMARK("50 microseconds"){ return sleep::sleep_us(us); };
	us = 10;
	BENCHMARK("10 microseconds"){ return sleep::sleep_us(us); };
	us = 5;
	BENCHMARK("5 microseconds"){ return sleep::sleep_us(us); };
	us = 1;
	BENCHMARK("1 microseconds"){ return sleep::sleep_us(us); };
}