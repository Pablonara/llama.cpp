#include "common.h"
#include "chat.h"
#include <cassert>
#include <iostream>

void test_capybara_reasoning_basic() {
    std::cout << "Testing basic capybara reasoning extraction..." << std::endl;
    
    std::string input = "<reasoning>Let me think about this step by step...</reasoning>The answer is 42.";
    
    common_chat_syntax syntax = {
        .format = COMMON_CHAT_FORMAT_CAPYBARA,
        .reasoning_format = COMMON_REASONING_FORMAT_CAPYBARA,
        .reasoning_in_content = false,
        .thinking_forced_open = false,
        .parse_tool_calls = false,
    };
    
    auto result = common_chat_parse(input, false, syntax);
    
    assert(!result.reasoning_content.empty());
    assert(result.reasoning_content == "Let me think about this step by step...");
    assert(result.content == "The answer is 42.");
    
    std::cout << "✓ Basic capybara reasoning extraction works" << std::endl;
}

void test_capybara_reasoning_forced_open() {
    std::cout << "Testing capybara reasoning with thinking_forced_open..." << std::endl;
    
    std::string input = "Let me think about this step by step...</reasoning>The answer is 42.";
    
    common_chat_syntax syntax = {
        .format = COMMON_CHAT_FORMAT_CAPYBARA,
        .reasoning_format = COMMON_REASONING_FORMAT_CAPYBARA,
        .reasoning_in_content = false,
        .thinking_forced_open = true,
        .parse_tool_calls = false,
    };
    
    auto result = common_chat_parse(input, false, syntax);
    
    assert(!result.reasoning_content.empty());
    assert(result.reasoning_content == "Let me think about this step by step...");
    assert(result.content == "The answer is 42.");
    
    std::cout << "✓ Capybara reasoning with thinking_forced_open works" << std::endl;
}

void test_capybara_reasoning_in_content() {
    std::cout << "Testing capybara reasoning_in_content mode..." << std::endl;
    
    std::string input = "<reasoning>Let me think about this step by step...</reasoning>The answer is 42.";
    
    common_chat_syntax syntax = {
        .format = COMMON_CHAT_FORMAT_CAPYBARA,
        .reasoning_format = COMMON_REASONING_FORMAT_CAPYBARA,
        .reasoning_in_content = true,
        .thinking_forced_open = false,
        .parse_tool_calls = false,
    };
    
    auto result = common_chat_parse(input, false, syntax);
    
    assert(result.reasoning_content.empty());
    assert(result.content.find("<reasoning>") != std::string::npos);
    assert(result.content.find("Let me think about this step by step...") != std::string::npos);
    assert(result.content.find("</reasoning>") != std::string::npos);
    assert(result.content.find("The answer is 42.") != std::string::npos);
    
    std::cout << "✓ Capybara reasoning_in_content mode works" << std::endl;
}

void test_capybara_no_reasoning() {
    std::cout << "Testing capybara format with no reasoning tags..." << std::endl;
    
    std::string input = "The answer is 42.";
    
    common_chat_syntax syntax = {
        .format = COMMON_CHAT_FORMAT_CAPYBARA,
        .reasoning_format = COMMON_REASONING_FORMAT_CAPYBARA,
        .reasoning_in_content = false,
        .thinking_forced_open = false,
        .parse_tool_calls = false,
    };
    
    auto result = common_chat_parse(input, false, syntax);
    
    assert(result.reasoning_content.empty());
    assert(result.content == "The answer is 42.");
    
    std::cout << "✓ Capybara format with no reasoning tags works" << std::endl;
}

void test_capybara_reasoning_format_names() {
    std::cout << "Testing capybara reasoning format name functions..." << std::endl;
    
    // Test name to enum conversion
    auto format = common_reasoning_format_from_name("capybara");
    assert(format == COMMON_REASONING_FORMAT_CAPYBARA);
    
    // Test enum to name conversion
    const char* name = common_reasoning_format_name(COMMON_REASONING_FORMAT_CAPYBARA);
    assert(std::string(name) == "capybara");
    
    std::cout << "✓ Capybara reasoning format name functions work" << std::endl;
}

int main() {
    std::cout << "Running Capybara reasoning format tests..." << std::endl << std::endl;
    
    try {
        test_capybara_reasoning_basic();
        test_capybara_reasoning_forced_open();
        test_capybara_reasoning_in_content();
        test_capybara_no_reasoning();
        test_capybara_reasoning_format_names();
        
        std::cout << std::endl << "All Capybara tests passed! ✅" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
}