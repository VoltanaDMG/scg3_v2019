
/**
 * Forward declaration of classes with shared and unique pointers.\n
 *   Class\n
 *   ClassSP - shared_pointer<Class>\n
 *   classUP - unique_pointer<Class>
 */
#define PRG_DECLARE_CLASS(TypeName) \
    class TypeName; \
    typedef std::shared_ptr<TypeName> TypeName##SP; \
    typedef std::unique_ptr<TypeName> TypeName##UP;

PRG_DECLARE_CLASS(Timer);

#pragma once
class Timer
{
public:
	/**
	 * Constructor
	 */
	Timer();
	/**
	 * Destructor
	 */
	virtual ~Timer();
	/**
	 * Create shared pointer.
     */
	static TimerSP create();
	Timer* reset();
	unsigned long long milliseconds_elapsed() const;

private:
	typedef std::chrono::steady_clock clock;
	typedef std::chrono::milliseconds milliseconds;

	clock::time_point start = clock::now();
};

