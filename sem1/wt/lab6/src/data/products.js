const products = [
  {
    id: 1,
    name: "StormGuard Rain Jacket",
    category: "Rainwear",
    price: 2499,
    image: "/images/rain-jacket.svg",
    shortDescription: "Lightweight waterproof jacket with taped seams.",
    description:
      "A breathable shell built for Mumbai-style downpours. Taped seams keep water out while the mesh lining keeps you from overheating on humid days.",
    features: [
      "Fully taped seams",
      "Adjustable hood",
      "Two zip pockets",
      "Packs into its own pocket",
    ],
  },
  {
    id: 2,
    name: "CloudShell Poncho",
    category: "Rainwear",
    price: 799,
    image: "/images/cloudshell-poncho.svg",
    shortDescription: "Roomy reusable poncho that covers you and your bag.",
    description:
      "Slip it on over your clothes and backpack in seconds. The wide cut keeps you dry on a bike, a scooter or a long walk to the station.",
    features: [
      "Fits over backpacks",
      "Snap-button sides",
      "Folds into a small pouch",
      "Reusable material",
    ],
  },
  {
    id: 3,
    name: "UrbanShield Raincoat",
    category: "Rainwear",
    price: 3299,
    image: "/images/urbanshield-raincoat.svg",
    shortDescription: "Knee-length raincoat that looks sharp at the office.",
    description:
      "A long, clean-cut raincoat for daily commuters. Water beads off the outer fabric and the quick-dry lining keeps you comfortable all day.",
    features: [
      "Knee-length cut",
      "Water-repellent fabric",
      "Concealed button front",
      "Inner phone pocket",
    ],
  },
  {
    id: 4,
    name: "Drift Compact Umbrella",
    category: "Umbrellas",
    price: 599,
    image: "/images/drift-umbrella.svg",
    shortDescription: "Pocket-sized folding umbrella under 300 g.",
    description:
      "Small enough for any bag, strong enough for heavy rain. The three-fold design opens wide and dries quickly.",
    features: [
      "Three-fold design",
      "Weighs under 300 g",
      "Wide 95 cm canopy",
      "Includes carry sleeve",
    ],
  },
  {
    id: 5,
    name: "WindFlex Automatic Umbrella",
    category: "Umbrellas",
    price: 899,
    image: "/images/windflex-umbrella.svg",
    shortDescription: "One-touch open and close with a windproof frame.",
    description:
      "Press one button to open or close. The flexible fibreglass ribs bend in strong gusts instead of snapping.",
    features: [
      "One-touch auto open/close",
      "Windproof fibreglass ribs",
      "Non-slip handle",
      "Double-layer canopy",
    ],
  },
  {
    id: 6,
    name: "StormLite Travel Umbrella",
    category: "Umbrellas",
    price: 749,
    image: "/images/stormlite-umbrella.svg",
    shortDescription: "Light travel umbrella with a reflective trim.",
    description:
      "Made for people who are always on the move. The reflective trim makes you easier to spot on dark, rainy evenings.",
    features: [
      "Reflective edge trim",
      "Rust-proof frame",
      "Slim travel size",
      "Quick-dry canopy",
    ],
  },
  {
    id: 7,
    name: "Monsoon Explorer Backpack",
    category: "Waterproof Gear",
    price: 1899,
    image: "/images/explorer-backpack.svg",
    shortDescription: "Everyday 25L backpack with a water-resistant shell.",
    description:
      "A daily backpack with a coated shell and sealed zips. There is a padded laptop sleeve and enough room for a day of college or work.",
    features: [
      "25 litre capacity",
      "Padded laptop sleeve",
      "Sealed zips",
      "Rain cover included",
    ],
  },
  {
    id: 8,
    name: "HydroPack Waterproof Backpack",
    category: "Waterproof Gear",
    price: 2799,
    image: "/images/hydropack-backpack.svg",
    shortDescription: "Roll-top backpack that stays fully dry inside.",
    description:
      "A roll-top closure and welded seams make this pack genuinely waterproof, so your gadgets and documents stay dry even in a downpour.",
    features: [
      "Roll-top closure",
      "Welded seams",
      "30 litre capacity",
      "Padded shoulder straps",
    ],
  },
  {
    id: 9,
    name: "AquaShield Phone Pouch",
    category: "Waterproof Gear",
    price: 349,
    image: "/images/phone-pouch.svg",
    shortDescription: "Touch-friendly pouch that keeps your phone dry.",
    description:
      "Use your phone through the clear window while it stays sealed from rain and splashes. A neck cord keeps it close.",
    features: [
      "Works with touchscreens",
      "Fits phones up to 6.8 inches",
      "Secure seal lock",
      "Detachable neck cord",
    ],
  },
  {
    id: 10,
    name: "TrailGrip Rain Boots",
    category: "Footwear",
    price: 1999,
    image: "/images/trailgrip-boots.svg",
    shortDescription: "Ankle-high rain boots with deep-grip soles.",
    description:
      "Walk through waterlogged streets with confidence. The deep tread grips wet tiles and the lining stays comfortable for hours.",
    features: [
      "Deep anti-slip tread",
      "Fully waterproof upper",
      "Soft fabric lining",
      "Easy pull-on loop",
    ],
  },
  {
    id: 11,
    name: "DryStep Shoe Covers",
    category: "Accessories",
    price: 299,
    image: "/images/drystep-covers.svg",
    shortDescription: "Stretchy covers that protect your shoes from rain.",
    description:
      "Pull them over your sneakers or office shoes before you step out. They wash easily and fold flat when the sun is back.",
    features: [
      "Fit most shoe sizes",
      "Non-slip sole",
      "Washable and reusable",
      "Folds flat",
    ],
  },
  {
    id: 12,
    name: "QuickDry Microfiber Towel",
    category: "Accessories",
    price: 449,
    image: "/images/quickdry-towel.svg",
    shortDescription: "Compact towel that dries in minutes.",
    description:
      "Wipe off rain, sweat or splashes and hang it up. This microfiber towel absorbs a lot, dries fast and takes almost no space.",
    features: [
      "Absorbs fast",
      "Dries in minutes",
      "Compact and light",
      "Loop for hanging",
    ],
  },
  {
    id: 13,
    name: "AquaTrek Waterproof Shoes",
    category: "Footwear",
    price: 2299,
    image: "/images/aquatrek-shoes.svg",
    shortDescription: "Waterproof sneakers you can wear all day.",
    description:
      "These look like regular sneakers but keep water out. A breathable membrane stops your feet from getting sweaty.",
    features: [
      "Waterproof membrane",
      "Cushioned insole",
      "Grippy rubber outsole",
      "Quick-dry lining",
    ],
  },
  {
    id: 14,
    name: "PackLite Dry Bag",
    category: "Waterproof Gear",
    price: 999,
    image: "/images/packlite-drybag.svg",
    shortDescription: "10L dry bag for treks, bikes and beach days.",
    description:
      "Roll the top, clip it shut and your things stay dry. A handy extra bag for monsoon treks and road trips.",
    features: [
      "10 litre capacity",
      "Roll-and-clip closure",
      "Tough coated fabric",
      "Shoulder strap",
    ],
  },
];

export const categories = [
  "Rainwear",
  "Umbrellas",
  "Waterproof Gear",
  "Footwear",
  "Accessories",
];
export default products;
