import {
  createContext,
  createEffect,
  createSignal,
  onCleanup,
  useContext,
} from "solid-js";

const EventContext = createContext();

function EventProvider(props) {
  const [eventData, setEventData] = createSignal({ name: "none" });

  createEffect(() => {
    console.log("Running event effect");
    const eventSource = new EventSource("/api/v1/events");

    eventSource.onmessage = (event) => {
      console.log(event.data);
      const sportData = JSON.parse(event.data);
      setEventData({ ...sportData });
    };

    onCleanup(() => {
      console.log("Quitting event effect");
      eventSource.close();
    });
  });

  return (
    <EventContext.Provider value={eventData}>
      {props.children}
    </EventContext.Provider>
  );
}

function useEvent() {
  return useContext(EventContext);
}

export { EventProvider, useEvent };
