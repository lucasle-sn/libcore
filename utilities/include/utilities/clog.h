#ifndef UTILITIES_CLOG_H
#define UTILITIES_CLOG_H

#include <fmt/core.h>
#include <fmt/format.h>
#include <cstdarg>
#include <cstdio>
#include <mutex>

#include <utilities/log_config.h>

namespace qle {

/**
 * @brief CLogger class
 */
class CLogger {
 public:
  /**
   * @brief Constructor deleted
   */
  CLogger() = delete;

  /**
   * @brief Copy constructor deleted
   */
  CLogger(const CLogger &) = delete;

  /**
   * @brief Move constructor deleted
   */
  CLogger(CLogger &&) = delete;

  /**
   * @brief Copy assignment deleted
   */
  CLogger &operator=(const CLogger &) = delete;

  /**
   * @brief Move assignment deleted
   */
  CLogger &operator=(CLogger &&) = delete;

  /**
   * @brief Construct a new CLogger object
   *
   * @param logger_name CLogger name
   */
  explicit CLogger(const char *logger_name) noexcept
      : logger_name_(logger_name) {
    logger_config_ = LoggerConfig::create();
  }

  /**
   * @brief Destroy the CLogger object
   */
  ~CLogger() = default;

  /**
   * @brief Log trace to stdout
   *
   * @param format Format
   * @param args Follow-up arguments
   */
  template <typename... Args>
  void trace(const char *format, Args... args) noexcept {
    log(LogLevel::TRACE, format, args...);
  }

  /**
   * @brief Log debug to stdout
   *
   * @param format Format
   * @param args Follow-up arguments
   */
  template <typename... Args>
  void debug(const char *format, Args... args) noexcept {
    log(LogLevel::DEBUG, format, args...);
  }

  /**
   * @brief Log info to stdout
   *
   * @param format Format
   * @param args Follow-up arguments
   */
  template <typename... Args>
  void info(const char *format, Args... args) noexcept {
    log(LogLevel::INFO, format, args...);
  }

  /**
   * @brief Log warning to stderr
   *
   * @param format Format
   * @param args Follow-up arguments
   */
  template <typename... Args>
  void warn(const char *format, Args... args) noexcept {
    log(LogLevel::WARNING, format, args...);
  }

  /**
   * @brief Log error to stderr
   *
   * @param format Format
   * @param args Follow-up arguments
   */
  template <typename... Args>
  void error(const char *format, Args... args) noexcept {
    log(LogLevel::ERROR, format, args...);
  }

 private:
  /**
   * @brief Log data
   *
   * @param level Log level
   * @param format Format
   * @param args Follow-up arguments
   */
  template <typename... Args>
  void log(LogLevel::Level level, const char *format, Args... args) noexcept {
    if (!LogLevel::is_valid_log_level(level)) {
      return;
    }

    if (level < logger_config_->loglevel()) {
      return;
    }

    std::string full_log_msg =
        fmt::format("[{}] {}: {}", LogLevel::log_level_to_string(level),
                    logger_name_, fmt::format(format, args...));

    std::lock_guard<std::mutex> guard(logger_config_->logmutex);
    if (logger_config_->logfile()) {
      if (level != LogLevel::DISABLED) {
        fprintf(logger_config_->logfile(), "%s\n", full_log_msg.c_str());
      }
      return;
    }
    switch (level) {
      case LogLevel::TRACE:
      case LogLevel::DEBUG:
      case LogLevel::INFO:
        std::cout << full_log_msg << std::endl;
        break;
      case LogLevel::WARNING:
      case LogLevel::ERROR:
        std::cerr << full_log_msg << std::endl;
        break;
      case LogLevel::DISABLED:
      default:
        return;
    }
  }

  const char *logger_name_;               ///< Logger name
  LoggerConfig *logger_config_{nullptr};  ///< Logger config
};

}  // namespace qle

#endif  // UTILITIES_CLOG_H
