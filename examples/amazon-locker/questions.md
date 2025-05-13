1. Functional Follow-Up Questions
🔹 How do you handle oversized packages?
Answer:

Reject them at validation time.

Or use a fallback location with larger lockers.

Could add a new XL size in the enum.

🔹 What if the customer doesn’t pick up the package in time?
Answer:

System marks it expired (already implemented).

Trigger notification (Observer).

Queue the locker for admin intervention or rerouting.

🔹 How do you ensure the correct user picks up the package?
Answer:

Use a secure OTP or QR code sent to registered email/phone.

Could require user to login with OTP before pickup (AuthService can evolve to support this).

🔹 Can a locker be reassigned if a package is expired?
Answer:

Yes — after expiry, cleanup service marks locker as AVAILABLE.

Package could be marked as RETURNED or archived.

✅ 2. Design/Scalability Questions
🔹 How would you scale this system to serve multiple cities or countries?
Answer:

Shard LockerLocation data by region.

Use a distributed store (e.g. DynamoDB) or a central LockerAssignment microservice.

Cache available lockers per location to reduce lookup latency.

🔹 What happens if two delivery agents try to assign the same locker?
Answer:

Use a mutex/lock at the locker or location level.

Or, persist locker state atomically in a database (e.g. using transactions or optimistic locking).

🔹 How would you implement high availability?
Answer:

Decouple services: AuthService, LockerService, NotificationService.

Run stateless services in multiple zones.

Use message queues for async delivery and retries (e.g., failed notification).

✅ 3. Maintainability/Extensibility Questions
🔹 How would you add a new notification channel (e.g., WhatsApp)?
Answer:

Add a new class that implements IObserver (thanks to Observer Pattern).

Register it in NotificationManager.

🔹 If we wanted smart lockers (temperature-controlled), how would you support that?
Answer:

Extend the Locker class to include properties like isTemperatureControlled.

Create a new LockerSelectionStrategy that filters based on this property.

🔹 What if users want to reserve a locker ahead of delivery?
Answer:

Add a reservation status and timestamp.

Only allow assignment if not already reserved or expired.

🔹 Can you support multiple packages per locker?
Answer:

Convert assignedPackageId to a vector<string> packageIds in Locker.

Update logic to allow partial pickups or space checking.

✅ 4. Design Pattern Questions
🔹 Why did you choose Strategy Pattern for locker assignment?
Answer:

It allows plugging in multiple selection policies — proximity, temperature, usage — without changing LockerService.

🔹 Why is Singleton useful here? Is it always a good idea?
Answer:

For stateless services like Auth or Notification, Singleton prevents multiple conflicting instances.
But in large systems, Singletons can be harder to test or replace. Dependency Injection is often preferred at scale.

🔹 If you had to log every delivery attempt, where would you put it?
Answer:

Create a Command object for each operation (DeliverCommand, PickupCommand) and log/store it.

Use a CommandHandler to execute and persist.

✅ Tips for Answering Follow-Ups
Always mention trade-offs: “We can cache locker availability for speed, but risk staleness.”

Tie in design patterns: “We can use Strategy for dynamic pricing per locker size.”

Mention scale/maintainability: “This scales with minimal change to core logic.”