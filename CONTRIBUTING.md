# Contributing to crypto-cli

Thank you for your interest in contributing to crypto-cli! This document provides guidelines and instructions for contributing.

## Development Setup

1. **Fork and Clone**
   ```bash
   git clone <your-fork-url>
   cd crypto-cli
   ```

2. **Install Dependencies**
   - libcurl
   - libcjson
   - GCC or compatible C compiler
   - Make

3. **Build**
   ```bash
   make
   ```

4. **Test**
   ```bash
   ./bin/crypto btc
   ./bin/crypto bitcoin price
   ```

## Code Style

- Use C11 standard
- Follow existing code style (4 spaces indentation)
- Add comments for complex logic
- Use descriptive variable and function names
- Keep functions focused and modular

## Testing

- Test with various cryptocurrency symbols
- Test both full info and price-only modes
- Test error cases (invalid symbols, network failures)
- Verify memory management (no leaks)

## Pull Requests

1. Create a feature branch
2. Make your changes
3. Test thoroughly
4. Update documentation if needed
5. Submit pull request with clear description

## Adding New Features

- Keep the CLI interface simple and intuitive
- Maintain backward compatibility
- Update README.md with new features
- Add appropriate error handling

## Bug Reports

Please include:
- OS and version
- Compiler version
- Steps to reproduce
- Expected vs actual behavior
- Error messages (if any)

Thank you for contributing!

