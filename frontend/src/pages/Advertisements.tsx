import { For, Show, createSignal, onMount } from "solid-js";

import Header from "../components/Header";

function Advertisements() {
  const [newAd, setNewAd] = createSignal("");

  const endpoint = "/api/v1/advertisement";

  const [adList, setAdList] = createSignal([]);

  onMount(async () => {
    const resp = await fetch(endpoint);
    const data = await resp.json();

    console.log(data);
    if (data != null) {
      setAdList(data);
    }
  });

  const postToEndpoint = async function () {
    const ad = newAd();

    if (ad.length > 0) {
      const response = await fetch(endpoint, {
        method: "POST",
        body: JSON.stringify({ ad: ad }),
      });

      const data = await response.json();
      const tempAdList = Array.from(adList());

      tempAdList.push({ id: data["id"], ad: ad });
      setAdList(tempAdList);
    }
  };

  const deleteFromEndpoint = async function (adId) {
    const response = await fetch(endpoint, {
      method: "DELETE",
      body: JSON.stringify({ adId: adId }),
    });

    const data = await response.json();
    console.log(data);

    if (data != null) {
      setAdList(data);
    } else {
      setAdList([]);
    }
  };

  return (
    <>
      <Header>Advertisements</Header>
      <div class="flex justify-center font-normal">
        <div class="grid w-full max-w-xl grid-cols-1 gap-3">
          <label for="advertisementMessage" class="font-bold">
            New Advertisement
          </label>

          <textarea
            id="advertisementMessage"
            type="text"
            aria-label="advertisement message"
            name="advertisement message"
            placeholder="Enter new ad message.."
            maxlength="50"
            class="text-md block w-full rounded-lg border border-gray-300 bg-gray-50 p-2.5 placeholder:italic focus:border-gray-800 focus:outline-none focus:ring-0 focus:ring-gray-800"
            onChange={(e) => setNewAd(e.target.value)}
          />

          <button
            type="submit"
            class="justify-self-end rounded-full bg-primary px-2 py-1 font-medium text-white"
            onClick={() => {
              postToEndpoint();
              document.getElementById("advertisementMessage").value = "";
            }}
          >
            Add
          </button>

          <Show when={adList().length > 0}>
            <hr class="my-5 h-0.5 border-0 bg-text" />

            <table class="text-md w-full text-left text-text rtl:text-right">
              <thead class="text-md bg-background font-bold uppercase text-text">
                <tr>
                  <th scope="col" class="p-2">
                    Advertisement
                  </th>

                  <th scope="col" class="p-2 text-end">
                    Action
                  </th>
                </tr>
              </thead>

              <tbody>
                <For each={adList()}>
                  {(item, index) => (
                    <tr>
                      <th
                        scope="row"
                        class="px-2 py-2 font-medium text-gray-900"
                      >
                        {item["ad"]}
                      </th>

                      <td class="px-2 py-2 text-end uppercase">
                        <button
                          onClick={() => {
                            deleteFromEndpoint(item["id"]);
                          }}
                        >
                          Delete
                        </button>
                      </td>
                    </tr>
                  )}
                </For>
              </tbody>
            </table>
          </Show>
        </div>
      </div>
    </>
  );
}

export default Advertisements;
